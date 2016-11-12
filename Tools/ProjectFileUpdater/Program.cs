using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace ProjectFileUpdater
{
    class Program
    {
        static void Main(string[] args)
        {
            string executablePath = new Uri(Assembly.GetExecutingAssembly().CodeBase).LocalPath;
            string codeDirectory = Path.GetDirectoryName(executablePath);
            codeDirectory = Path.GetDirectoryName(codeDirectory);
            codeDirectory = Path.GetDirectoryName(codeDirectory);
            codeDirectory = Path.GetDirectoryName(codeDirectory);
            codeDirectory = Path.GetDirectoryName(codeDirectory);
            codeDirectory = Path.Combine(codeDirectory, "Competition");

            foreach (var templateFilePath in Directory.GetFiles(codeDirectory, "*.template"))
            {
                string instanceFileName = Path.GetFileNameWithoutExtension(templateFilePath);
                string instanceFilePath = Path.Combine(codeDirectory, instanceFileName);
                using (var projectFileStream = File.OpenRead(templateFilePath))
                {
                    using (var newProjectFileStream = File.OpenWrite(instanceFilePath))
                    {
                        XDocument doc = XDocument.Load(projectFileStream);
                        XElement includeNode = (XElement)doc.DescendantNodes().FirstOrDefault(n => n is XElement && ((XElement)n).Name.LocalName.Equals("ClIncludeTemplate"));
                        if (includeNode != null)
                        {
                            includeNode.Name = XName.Get("ItemGroup", includeNode.Name.Namespace.NamespaceName);
                            foreach (var headerFileName in Directory.GetFiles(codeDirectory, "*.h").OrderBy(fileName => fileName))
                            {
                                XElement includeElement = new XElement(XName.Get("ClInclude", includeNode.Name.Namespace.NamespaceName));
                                includeElement.Add(new XAttribute("Include", Path.GetFileName(headerFileName)));
                                includeNode.Add(includeElement);
                            }
                        }
                        XElement includeFilterNode = (XElement)doc.DescendantNodes().FirstOrDefault(n => n is XElement && ((XElement)n).Name.LocalName.Equals("ClIncludeFilterTemplate"));
                        if (includeFilterNode != null)
                        {
                            includeFilterNode.Name = XName.Get("ItemGroup", includeFilterNode.Name.Namespace.NamespaceName);
                            foreach (var headerFileName in Directory.GetFiles(codeDirectory, "*.h").OrderBy(fileName => fileName))
                            {
                                XElement includeFilterElement = new XElement(XName.Get("ClInclude", includeFilterNode.Name.Namespace.NamespaceName));
                                includeFilterElement.Add(new XAttribute("Include", Path.GetFileName(headerFileName)));
                                XElement filterElement = new XElement(XName.Get("Filter", includeFilterNode.Name.Namespace.NamespaceName));
                                filterElement.Add(new XText("Header Files"));
                                includeFilterElement.Add(filterElement);
                                includeFilterNode.Add(includeFilterElement);
                            }
                        }

                        XElement compileNode = (XElement)doc.DescendantNodes().FirstOrDefault(n => n is XElement && ((XElement)n).Name.LocalName.Equals("ClCompileTemplate"));
                        if (compileNode != null)
                        {
                            compileNode.Name = XName.Get("ItemGroup", compileNode.Name.Namespace.NamespaceName);
                            foreach (var headerFileName in Directory.GetFiles(codeDirectory, "*.cpp").OrderBy(fileName => fileName))
                            {
                                if (!string.Equals(Path.GetFileNameWithoutExtension(headerFileName), "stdafx", StringComparison.OrdinalIgnoreCase))
                                {
                                    XElement compileElement = new XElement(XName.Get("ClCompile", compileNode.Name.Namespace.NamespaceName));
                                    compileElement.Add(new XAttribute("Include", Path.GetFileName(headerFileName)));
                                    compileNode.Add(compileElement);
                                }
                            }
                        }

                        XElement compileFilterNode = (XElement)doc.DescendantNodes().FirstOrDefault(n => n is XElement && ((XElement)n).Name.LocalName.Equals("ClCompileFilterTemplate"));
                        if (compileFilterNode != null)
                        {
                            compileFilterNode.Name = XName.Get("ItemGroup", compileFilterNode.Name.Namespace.NamespaceName);
                            foreach (var headerFileName in Directory.GetFiles(codeDirectory, "*.cpp").OrderBy(fileName => fileName))
                            {
                                XElement compileFilterElement = new XElement(XName.Get("ClCompile", compileFilterNode.Name.Namespace.NamespaceName));
                                compileFilterElement.Add(new XAttribute("Include", Path.GetFileName(headerFileName)));
                                XElement filterElement = new XElement(XName.Get("Filter", compileFilterNode.Name.Namespace.NamespaceName));
                                filterElement.Add(new XText("Source Files"));
                                compileFilterElement.Add(filterElement);
                                compileFilterNode.Add(compileFilterElement);
                            }
                        }
                        doc.Save(newProjectFileStream);
                    }
                }
            }
        }
    }
}
