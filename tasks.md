# Vector

## Member functions

- [ ] `(constructor)`: Construct vector
- [x] `(destructor)`: Vector destructor
- [ ] `operator=`: Assign content

#### Iterators:
- [x] `begin`: Return iterator to beginning
- [x] `end`: Return iterator to end
- [x] `rbegin`: Return reverse iterator to reverse beginning
- [x] `rend`: Return reverse iterator to reverse end

#### Capacity:
- [x] `size`: Return size
- [x] `max_size`: Return maximum size
- [x] `resize`: Change size
- [x] `capacity`: Return size of allocated storage capacity
- [x] `empty`: Test whether vector is empty
- [x] `reserve`: Request a change in capacity

#### Element access:
- [x] `operator[]`: Access element
- [x] `at`: Access element
- [x] `front`: Access first element
- [x] `back`: Access last element

#### Modifiers:
- [x] `assign`: Assign vector content
- [x] `push_back`: Add element at the end
- [x] `pop_back`: Delete last element
- [ ] `insert`: Insert elements
- [ ] `erase`: Erase elements
- [ ] `swap`: Swap content
- [x] `clear`: Clear content

#### Allocator:
- [x] `get_allocator`: Get allocator

## Non-member function overloads
- [ ] `relational operators`: Relational operators for vector (function template )
- [ ] `swap`: Exchange contents of vectors (function template )

# Map

## Member functions

- [ ] `(constructor)`: Construct map
- [ ] `(destructor)`: Map destructor
- [ ] `operator=`: Copy container content

#### Iterators:
- [ ] `begin`: Return iterator to beginning
- [ ] `end`: Return iterator to end
- [ ] `rbegin`: Return reverse iterator to reverse beginning
- [ ] `rend`: Return reverse iterator to reverse end

#### Capacity:
- [ ] `empty`: Test whether container is empty
- [ ] `size`: Return container size
- [ ] `max_size`: Return maximum size

#### Element access:
- [ ] `operator[]`: Access element

#### Modifiers:
- [ ] `insert`: Insert elements
- [ ] `erase`: Erase elements
- [ ] `swap`: Swap content
- [ ] `clear`: Clear content

#### Observers:
- [ ] `key_comp`: Return key comparison object
- [ ] `value_comp`: Return value comparison object

#### Operations:
- [ ] `find`: Get iterator to element
- [ ] `count`: Count elements with a specific key
- [ ] `lower_bound`: Return iterator to lower bound
- [ ] `upper_bound`: Return iterator to upper bound
- [ ] `equal_range`: Get range of equal elements

#### Allocator:
- [ ] `get_allocator`: Get allocator