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
            string projectFileName = Path.Combine(codeDirectory, "Competition.vs2013.vcxproj.template");
            string newProjectFileName = Path.Combine(codeDirectory, "Competition.vs2013.vcxproj");
            using (var projectFileStream = File.OpenRead(projectFileName))
            {
                using (var newProjectFileStream = File.OpenWrite(newProjectFileName))
                {
                    XDocument doc = XDocument.Load(projectFileStream);
                    XElement includeNode = (XElement)doc.DescendantNodes().First(n => n is XElement && ((XElement)n).Name.LocalName.Equals("ClIncludeTemplate"));
                    includeNode.Name = XName.Get("ItemGroup", includeNode.Name.Namespace.NamespaceName);
                    foreach (var headerFileName in Directory.GetFiles(codeDirectory, "*.h").OrderBy(fileName => fileName))
                    {
                        XElement includeElement = new XElement(XName.Get("ClInclude", includeNode.Name.Namespace.NamespaceName));
                        includeElement.Add(new XAttribute("Include", Path.GetFileName(headerFileName)));
                        includeNode.Add(includeElement);
                    }
                    XElement compileNode = (XElement)doc.DescendantNodes().First(n => n is XElement && ((XElement)n).Name.LocalName.Equals("ClCompileTemplate"));
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
                    doc.Save(newProjectFileStream);
                }
            }

        }
    }
}
