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
