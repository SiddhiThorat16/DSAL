'''
==============================================================================================================================================
A1) Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s telephone number.
==============================================================================================================================================
'''
size = int(input("Enter Size of Telephone Book Database: "))
client_list = [None] * size

def add_client():
    is_full = True  # Check if database is or not
    for entry in client_list:
        if entry is None:
            is_full = False
            break
    
    if is_full:
        print("Database is full...can't insert new record...Sorry!!!")
        return
    
    client_id = int(input("client id : "))
    name = input("client name : ")
    telephone = input("client telephone Number : ")
    client_details = [client_id, name, telephone]

    index = client_id % size
    # Inserting record using linear
    # probing in case of collision
    for i in range(size):
        if client_list[index] == None:
            client_list[index] = client_details
            print("Client details are added successfully")
            break
        else:
            index = (index + 1) % size
    print("\n Client List :", client_list)

def search_client():
    client_id = int(input("Enter client id to be search: "))
    index = client_id % size
    for i in range(size):
        if client_list[index] != None:
            if client_list[index][0] == client_id:
                print("client is a found at index ", index, client_list[index])
                break
        index = (index + 1) % size
    else:
        print("element is not found")

def delete_client():
    client_id = int(input("Enter client id to delete record: "))
    index = client_id % size
    for i in range(size):
        if client_list[index] != None:
            if client_list[index][0] == client_id:
                client_list[index] = None
                print("Client Telephone Record Delete Successfully...")
                break
        index = (index + 1) % size
    else:
        print("element is not found")

def Main():
   while True:
       print("\t 1 : ADD Client's Telephone Data.")
       print("\t 2 : SEARCH Client's Telephone Data.")
       print("\t 3 : DELETE Client's Telephone Data.")
       print("\t 4 : Exit")
       ch = int(input("Enter your choice : "))
       if ch == 1:
           add_client()
       elif ch == 2:
           search_client()
       elif ch == 3:
           delete_client()
       elif ch == 4:
           print("End of Program")
           break
       else:
           print("Wrong choice entered !! Try again")

Main()

'''
A1) Hash Table Implementation for Telephone Book (Using Linear Probing)
Theory Concepts
Hash Table is a data structure used for efficient storage and retrieval using a key-value pair format. It uses a hash function to compute the index from a key.

Hash Function:
A function that converts the key (here, client ID) to a valid array index using:

python
Copy
Edit
index = client_id % size
Collision:
When two keys produce the same hash index, a collision occurs.

Collision Resolution (Linear Probing):
If a collision happens, linear probing checks the next available slot in the array.

Practical Code Explanation
1. Initialization

python
Copy
Edit
size = int(input("Enter Size of Telephone Book Database: "))
client_list = [None] * size
Creates a list of a specified size to hold client data. Each slot starts as None.

2. Function: add_client()

Checks if the hash table is full.

Takes client ID, name, and telephone number as input.

Computes the hash index using modulo operation.

If the slot is occupied, it moves linearly to the next slot.

Inserts the client record at the available index.

3. Function: search_client()

Takes client ID as input.

Computes the starting index using the hash function.

Searches linearly through the table for the matching client ID.

If found, displays the client’s data.

4. Function: delete_client()

Takes client ID as input.

Searches for the ID using the same probing strategy.

If found, deletes the entry by setting it to None.

5. Function: Main()

Provides a menu for the user:

Add client

Search client

Delete client

Exit

Keeps running in a loop until the user selects exit.

Important Viva Questions and Answers
Q1. What is the advantage of hashing?
Hashing allows fast data access in average-case constant time O(1).

Q2. Why use linear probing?
To resolve collisions by checking subsequent slots in the array.

Q3. What are the limitations of this method?
It suffers from clustering and performance degrades as the table fills.

Q4. What happens if the table is full?
No new entries can be inserted; insertion is rejected.
'''


'''
==============================================================================================================================================================
A2) For given set of elements create skip list. Find the element in the set that is closest to some given value. (note: Decide the level of element in the list Randomly with some upper limit).
==============================================================================================================================================================
'''
import random

class SkipNode:
    def __init__(self, value, level):
        self.value = value
        self.forward = [None] * (level + 1)

class SkipList:
    def __init__(self, max_level):
        self.max_level = max_level
        self.header = SkipNode(None, max_level)
        self.level = 0

    def _random_level(self):
        level = 0
        while random.random() < 0.5 and level < self.max_level:
            level += 1
        return level

    def insert(self, value):
        update = [None] * (self.max_level + 1)
        current = self.header

        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
            update[i] = current

        new_level = self._random_level()
        if new_level > self.level:
            for i in range(self.level + 1, new_level + 1):
                update[i] = self.header
            self.level = new_level

        new_node = SkipNode(value, new_level)
        for i in range(new_level + 1):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node

    def find_closest(self, target):
        current = self.header
        closest = None
        min_diff = float('inf')

        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < target:
                current = current.forward[i]

        if current.forward[0]:
            current = current.forward[0]

        while current:
            diff = abs(current.value - target)
            if diff < min_diff:
                min_diff = diff
                closest = current.value
            current = current.forward[0]
        return closest

elements = [7, 9, 11, 26, 39, 44, 58, 90]
max_level = 3
skip_list = SkipList(max_level)

for element in elements:
    skip_list.insert(element)

target1 = 16
print(f"Closest to {target1}: {skip_list.find_closest(target1)}")

target2 = -5
print(f"Closest to {target2}: {skip_list.find_closest(target2)}")

target3 = int(input("Enter target of Your choice: "))
print(f"Closest to {target3}: {skip_list.find_closest(target3)}")

target4 = 46
print(f"Closest to {target4}: {skip_list.find_closest(target4)}")


'''
A2) Skip List for Closest Element Search
Theory Concepts
Skip List is a probabilistic alternative to balanced trees. It is built in multiple levels. Each level allows skipping over multiple elements, making search, insert, and delete operations efficient.

Structure:

Consists of multiple linked lists.

The base level contains all elements.

Higher levels contain a subset for faster traversal.

Each node contains forward pointers to other nodes on each level.

Randomization in Level Assignment:

Each node is assigned a random level.

This ensures balanced structure without complex re-balancing.

Practical Code Explanation
1. Class: SkipNode

python
Copy
Edit
class SkipNode:
    def __init__(self, value, level):
        self.value = value
        self.forward = [None] * (level + 1)
Represents each node in the skip list, where forward holds references to next nodes on different levels.

2. Class: SkipList

python
Copy
Edit
class SkipList:
    def __init__(self, max_level):
        self.max_level = max_level
        self.header = SkipNode(None, max_level)
        self.level = 0
Initializes the skip list with a header node and defines the maximum allowed level.

3. Method: _random_level()
Generates a random level for new nodes based on a geometric distribution with probability 0.5.

4. Method: insert(value)

Traverses the list from the top level to find insertion points.

Maintains an update list to record locations where the new node needs to be connected.

Inserts the new node and updates forward pointers accordingly.

5. Method: find_closest(target)

Traverses from the highest level down to the base level to approach the closest value less than or equal to the target.

Then proceeds forward on level 0 to find the element closest to the target in absolute value.

6. Example Execution

python
Copy
Edit
elements = [7, 9, 11, 26, 39, 44, 58, 90]
skip_list.insert(element)  # Adds each element to the skip list
skip_list.find_closest(16)  # Returns the element closest to 16
Important Viva Questions and Answers
Q1. What is the purpose of a skip list?
To allow fast searching, insertion, and deletion with average time complexity O(log n).

Q2. How is the level of a node determined?
Using a random function that decides the level probabilistically, usually with a 0.5 chance of promoting to a higher level.

Q3. How is searching performed in skip list?
Starts from the top level, moves forward as long as values are less than the target, then drops down one level.

Q4. What are the advantages of a skip list over BST?
Skip lists provide similar performance as balanced trees but are easier to implement and maintain because no rotations or re-balancing are needed.

Q5. What is the space complexity?
It is O(n log n) in the worst case due to multiple levels.



A **skip list** is a data structure that allows fast search, insertion, and deletion by maintaining multiple levels of linked lists, where each higher level skips over more elements to speed up access.

In simple terms: > A skip list is like a linked list with express lanes — the higher the lane, the more elements you skip — making it faster to find or insert elements.

'''
