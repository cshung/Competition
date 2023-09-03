enum sort_items_by_groups_respecting_dependencies {}

extension sort_items_by_groups_respecting_dependencies {
  class Solution {
    func sortItems(_ n: Int, _ m: Int, _ group: [Int], _ beforeItems: [[Int]]) -> [Int] {
      var group = group
      var groupMap = [Int: Int]()
      var groupGraph = [[Int]]()
      var groupMembers = [[Int]]()
      var withinGroupNames = [Int]()
      var withinGroupGraph = [[[Int]]]()

      for i in 0..<n {
        if let mappedGroup = groupMap[group[i]] {
          group[i] = mappedGroup
        } else {
          let newGroup = groupMembers.count
          if group[i] != -1 {
            groupMap[group[i]] = newGroup
          }
          group[i] = newGroup
          groupMembers.append([])
          groupGraph.append([])
          withinGroupGraph.append([])
        }

        let withinGroupName = groupMembers[group[i]].count
        withinGroupNames.append(withinGroupName)
        groupMembers[group[i]].append(i)
        withinGroupGraph[group[i]].append([])
      }

      for dst in 0..<n {
        for src in beforeItems[dst] {
          let srcGroup = group[src]
          let dstGroup = group[dst]

          if srcGroup == dstGroup {
            let srcName = withinGroupNames[src]
            let dstName = withinGroupNames[dst]
            withinGroupGraph[srcGroup][srcName].append(dstName)
          } else {
            groupGraph[srcGroup].append(dstGroup)
          }
        }
      }

      let groupOrder = topo(&groupGraph)
      if groupOrder == nil {
        return []
      }

      var answer = [Int]()
      for g in groupOrder! {
        let withinGroupOrder = topo(&withinGroupGraph[g])
        if withinGroupOrder == nil {
          return []
        }

        for w in withinGroupOrder! {
          answer.append(groupMembers[g][w])
        }
      }

      return answer
    }

    func topo(_ graph: inout [[Int]]) -> [Int]? {
      var colors = [Int: Int]()
      var answer = [Int]()

      for i in 0..<graph.count {
        if colors[i] == nil {
          let succeed = topoHelper(&graph, i, &colors, &answer)
          if !succeed {
            return nil
          }
        }
      }

      return answer.reversed()
    }

    func topoHelper(_ graph: inout [[Int]], _ v: Int, _ colors: inout [Int: Int], _ answer: inout [Int])
      -> Bool
    {
      colors[v] = 1

      for neighbor in graph[v] {
        if colors[neighbor] == nil {
          let succeed = topoHelper(&graph, neighbor, &colors, &answer)
          if !succeed {
            return false
          }
        } else if colors[neighbor] == 1 {
          return false
        }
      }

      colors[v] = 2
      answer.append(v)
      return true
    }
  }
  static func main() {
    print(
      Solution().sortItems(
        8, 2, [-1, -1, 1, 0, 0, 1, 0, -1], [[], [6], [5], [6], [3, 6], [], [], []]
      ))
  }
}
