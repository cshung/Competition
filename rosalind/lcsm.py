# http://rosalind.info/problems/lcsm/

from sys import stdin

# A suffix tree is a tree that represents all the suffixes of a string.
# This implementation allows the string to be extended at the end.

# Conceptually, the edges between the nodes has some characters on it.
# If one reads from the root node to a leaf node, one should read a
# suffix of the string. If the last character is unique, the tree
# contains all the suffixes.

# In any tree, except the root, every node has a parent edge, therefore
# We just store the edge information with the root. Because we have the
# string, and edge labels are always substrings, it is enough to just
# store the indices.

# The parent and suffix link fields are a bit unfortunate. They are 
# artifacts needed for the construction of the tree, but otherwise
# often unnecessary for using the tree.

class suffix_tree_node:

    def __init__(self):
        self._begin = 0
        self._end = 0
        self._parent = None
        self._first_child = None
        self._sibling = None
        self._suffix_link = None

    def get_child(self):
        return self._first_child
    
    def get_sibling(self):
        return self._sibling

#
# Here is an implementation of the Ukkonen's suffix tree construction algorithm
# The code is ported from my C++ implementation.
#
# The code is best understood by reading Dan Gusfield's book, because that's what
# I read and implemented it based on the book. It is chapter 6.1
#
# At a high level, the Ukkonen's algorithm allows growing the suffix tree one 
# character at a time. When the jth character is added, conceptually add all the 
# new suffixes to the tree. 
#
# Now start reading the append() method to understand how it is achieved.
#
class suffix_tree:

    def __init__(self):
        self._root = suffix_tree_node()
        self._last_internal_node = None
        self._start = 0
        self._s = []

    #
    # To add a character to a suffix tree, we add all the new suffixes to the tree
    # A suffix starting from _start is added to the tree by calling the extension method
    # 
    # To be consistent with the book, we will call each invocation of this method a phase.
    # 
    # Conceptually, _start should start from 1. It is not in the code because of the 
    # following rule:
    #
    # Once a leaf, always a leaf.
    # 
    # Suppose the last phase introduced a leaf node, in this phase, the only thing that we
    # need to do for this phase is to extend the edge label. All leaves must terminate at the 
    # end of the string, so if we implicity interprets the end of a leaf node to be the length
    # of the string and never explicitly store it, there is nothing we need to for them. Therefore
    # we skipped them all.
    #
    # Here begs the question, how do we know from 0 to _start - 1 were leaves in the last phase,
    # we will read more about that in the extension() method.
    #
    # Another things to notice is that if the already_in_tree returned by the extension method is True,
    # then we stop adding. There is because of the following rule:
    # 
    # Rule 3 is a show stopper
    #
    # Without referring to the book, this would be a mystery. What is rule 3 anyway? Here is an 
    # attempt to describe it succinctly. In the following, We use capital letter to represent strings
    # and lowercase character to represent characters. 
    #
    # Suppose we know that in the last extension, we were trying to insert aXb into the tree and we 
    # discovered that it is already there. That means aXb was a suffix in the last phase, so Xb must
    # also be a suffix in the last phase, so we can skip adding Xb. But not just that, any suffixes 
    # of Xb
    #
    # Another interesting piece in this code is the next_node_cursor and next_text_cursor. They can
    # be understood as the cursors where we search in the tree. We will soon see how they are used
    # in the extension method. For now, what we needed to know is that the extension() method have 
    # some way to speed up the next suffix insertion by maintaining these states.
    #
    # Now start reading the extension() method to see how a single suffix is added the tree.
    #
    def append(self, c):
        self._s.append(c)
        next_node_cursor = self._root
        next_text_cursor = self._start
        while (True):
            (already_in_tree, next_node_cursor, next_text_cursor) = self._extension(next_node_cursor, next_text_cursor)
            if already_in_tree:
                break
            else:
                self._start = self._start + 1
                if self._start == len(self._s):
                    break
    
    def get_root(self):
        return self._root

    def get_edge(self, node):
        length = self._length(node)
        return (node._begin, node._begin + length)

    #
    # The extension method add a suffix into the tree. We knew that the whole suffix besides the last character 
    # must be already in the tree during the last phase, therefore the first thing to do is to find out where
    # to add the last character. This is done by the search() method.
    #
    # Without looking into the search() method yet, it is useful to describe how do we represent a location in
    # the tree. One could imagine the tree labels are highlighted and the highlight stop somewhere. There are two
    # cases, either the highlighting is filling every edge label, or the highlighting fill the last edge partially.
    # In both case, we can represent the location by a pair, the node that owns the edge label, and the number of 
    # character filled by the edge label. That is how node_cursor and edge_cursor are interpreted.
    # 
    # text_cursor is simply the index of the next character to be added in the tree, so there is no need for a variable
    # for it, it is simply len(self._s).
    # 
    # the next_* variables are optimization. They allows the search to be short circuited so that it doesn't always 
    # start from the beginning. For now, just assume the search method always returns node_cursor and edge_cursor at
    # the right place.
    # 
    # Now here we are a few cases. The first branch is the case where the edge label is completely filled. If the node
    # is a leaf, there is nothing to do because the implicit interpretation of the leaf node will make sure the last 
    # character is added. That said, the already_in_tree flag stays False, because conceptually we still added the 
    # character to the tree.
    #
    # In case the edge label is completely filled and yet it is not a leaf, there are still two cases. It could be the 
    # case that there is a child node that continues with the last character. In that case we know the suffix is already
    # in the tree, so we set already_in_tree to True and stop. Otherwise we create a new leaf node and stop.
    #
    # Similarly, in case the edge label is not completely filled, we check if the last character is already in the tree.
    # If it does, we set already_in_tree to True and stop. Otherwise, we have to split the edge.
    #
    # In all cases, we maintain two variables. search_end and new_internal_node. search_end represents the last node we 
    # reached in the search, and new internal node represents the new internal node we created in the split edge case.
    # Theses two variables are used to build suffix links, a tool for speeding up searches.
    # 
    # Suffix links only applies to nodes that are not leaves and not root. If such a node represents the prefix 'aX', 
    # then the suffix link of it points to an internal node that represents X. Suppose during the insertion of 'aXY' 
    # found such a link, there we could use that to speed to the search for 'XY' in the next extension. It is obvious 
    # why it could be useful. What is not so obvious is that suffix links are easy to build and always available.
    #
    # A theorem in the book shows that if an internal node is created in the current extension, the next extension
    # would have found its suffix link. Therefore, we save the new_internal_node and set its suffix link to search_end
    # in the next iteration.
    #
    # To see how the suffix link is used to speed up the search, read the search() method now.
    #
    def _extension(self, next_node_cursor, next_text_cursor):
        node_cursor = next_node_cursor
        edge_cursor = self._length(node_cursor)
        already_in_tree = False
        (next_node_cursor, next_text_cursor, node_cursor, edge_cursor) = self._search(next_text_cursor, node_cursor, edge_cursor)
        next_text_char = self._s[len(self._s) - 1]
        search_end = None
        new_internal_node = None
        if edge_cursor == self._length(node_cursor):
            if (not (node_cursor == self._root)) and (node_cursor._first_child == None):
                pass
            else:
                search = node_cursor._first_child
                found = False
                while search != None:
                    if self._first_char(search) == next_text_char:
                        found = True
                        break
                    else:
                        search = search._sibling
                if found:
                    already_in_tree = True
                else:
                    new_leaf = suffix_tree_node()
                    new_leaf._begin = len(self._s) - 1
                    new_leaf._parent = node_cursor
                    new_leaf._sibling = node_cursor._first_child
                    node_cursor._first_child = new_leaf
            search_end = node_cursor
        else:
            next_tree_char = self._s[node_cursor._begin + edge_cursor]
            if next_text_char == next_tree_char:
                already_in_tree = True
            else:
                new_node = suffix_tree_node()
                new_leaf = suffix_tree_node()
                new_leaf._begin = len(self._s) - 1
                new_node._begin = node_cursor._begin
                new_node._end = node_cursor._begin + edge_cursor
                node_cursor._begin = node_cursor._begin + edge_cursor

                new_node._parent = node_cursor._parent
                new_leaf._parent = new_node
                node_cursor._parent = new_node

                new_node._sibling = new_node._parent._first_child
                new_node._parent._first_child = new_node

                search = new_node
                while not (search == None):
                    if (search._sibling == node_cursor):
                        search._sibling = search._sibling._sibling
                        break
                    search = search._sibling

                new_node._first_child = new_leaf
                new_leaf._sibling = node_cursor
                node_cursor._sibling = None

                new_internal_node = search_end = new_node

        if not (self._last_internal_node == None):
            self._last_internal_node._suffix_link = search_end
            self._last_internal_node = None

        if not (new_internal_node == None):
            self._last_internal_node = new_internal_node

        return (already_in_tree, next_node_cursor, next_text_cursor)

    #
    # The search method does two things, it starts from the node_cursor and edge_cursor
    # and find all the way the all but last character of the string. In the process, we
    # also prepare the next_node_cursor and next_text_cursor for the next search.
    #
    # The search for the location is pretty straightforward, there are two things worth
    # notice. When we hit an edge, we just simply moved the cursor without checking the 
    # character. It is because we knew it has to be correct. 
    # 
    # In the book, this implementation optimization is called the skip/count trick.
    #
    # We also set the next_node_cursor and next_text_cursor whenever we found a suffix link.
    # This is where the suffix link serve its purpose, it make the next search much faster 
    # by starting closest to where we already knew it must reach.
    #
    def _search(self, text_cursor, node_cursor, edge_cursor):
        next_node_cursor = self._root
        next_text_cursor = text_cursor + 1
        while (text_cursor < len(self._s) - 1):
            node_length = self._length(node_cursor)
            if (edge_cursor == node_length):
                if not (node_cursor._suffix_link == None):
                    next_node_cursor = node_cursor._suffix_link
                    next_text_cursor = text_cursor
                next_char = self._s[text_cursor]
                child_cursor = node_cursor._first_child
                while True:
                    if (self._first_char(child_cursor) == next_char):
                        node_cursor = child_cursor
                        edge_cursor = 0
                        break
                    else:
                        child_cursor = child_cursor._sibling
            else:
                text_move = len(self._s) - 1 - text_cursor
                edge_move = node_length - edge_cursor
                if text_move > edge_move:
                    move = edge_move
                else:
                    move = text_move
                edge_cursor = edge_cursor + move
                text_cursor = text_cursor + move
        return (next_node_cursor, next_text_cursor, node_cursor, edge_cursor)

    def _length(self, node):
        if node == self._root:
            return 0
        elif node._first_child == None:
            return len(self._s) - node._begin
        else:
            return node._end - node._begin

    def _first_char(self, node):
        return self._s[node._begin]

#
# This is a helper function for the longest_common_substring to perform a depth first search
# For each node, we can imagine that it represents the set of suffixes that is descendant 
# leaf nodes does.
#
# We would like to know, for each node, the set of suffixes contains all suffixes that 
# start with each DNA. The prefix represented by the node is then a candidate for the longest
# common substring.
#
# To compute that set of DNAs, we conceptually requires nodes to return what DNA do they have
# but if we do so, all nodes must combine all the answer. And the combination time would take
# time proportional to the number of children. That's not good. Instead, we can let the children
# fill in the blanks. If we hand the same blank paper to all children and each of them mark on 
# it, then the combination is done implicitly. The time required to spend on the nodes is not 
# dependent of the number of children, but just on the number of DNAs, that makes the algorithm
# O(NK), where N is the total length of the combined DNAs and K is the number of DNAs.
#
def longest_common_substring_find(tree, node, length, index, blanks, answer):
    (begin, end) = tree.get_edge(node)
    child = node.get_child()
    if child == None:
        begin = begin - length
        found = 0
        for i in range(0, len(index)):
            if begin <= index[i]:
                found = i
                break
        blanks[found] = True
    else:
        my_blanks = [False] * len(blanks)
        while not (child == None):
            longest_common_substring_find(tree, child, length + end - begin, index, my_blanks, answer)
            child = child.get_sibling()
        good = True
        for i in range(0, len(blanks)):
            blanks[i] = my_blanks[i] or blanks[i]
            good = good and my_blanks[i]
        if good:
            begin = begin - length
            length = end - begin
            if answer["max"] < length:
                answer["max"] = length
                answer["begin"] = begin
                answer["end"] = end

#
# To find the longest common substring of a collection of texts
# We concatenate the text together, using lowercase letters (which we know cannot be DNA characters)
# to separate them and build a suffix tree. The longest common substring must be a common prefix
# of all suffixes, so we will use the longest_common_substring_find to perform a depth first search
# for the answer
#
def longest_common_substring(texts):
    separator = 'a'
    count = 0
    tree = suffix_tree()
    index = []
    all = ""
    for text in texts:
        for c in text:
            tree.append(c)
            count = count + 1
        all = all + text + separator
        index.append(count)
        tree.append(separator)
        count = count + 1
        separator = chr(ord(separator) + 1)
    answer = {}
    answer["max"] = -1
    longest_common_substring_find(tree, tree.get_root(), 0, index, [False] * len(texts), answer)
    print(all[answer["begin"]:answer["end"]])

data = []
for line in stdin:
  data.append(line.strip())
data.append(">")

records = []
label = None
dna = ""
for line in data:
  if line[0] == '>':
    if label != None:
      records.append(dna)
    label = line[1:] 
    dna = ""
  else:
    dna = dna + line

longest_common_substring(records)