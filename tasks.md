# Vector

## Member functions

- [x] `(constructor)`: Construct vector
- [x] `(destructor)`: Vector destructor
- [x] `operator=`: Assign content

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
- [x] `insert`: Insert elements
- [x] `erase`: Erase elements
- [x] `swap`: Swap content
- [x] `clear`: Clear content

#### Allocator:
- [x] `get_allocator`: Get allocator

## Non-member function overloads
- [x] `relational operators`: Relational operators for vector
- [x] `swap`: Exchange contents of vectors

# Map

## Member functions

- [ ] `(constructor)`: Construct map
- [ ] `(destructor)`: Map destructor
- [ ] `operator=`: Copy container content

#### Iterators:
- [x] `begin`: Return iterator to beginning
- [x] `end`: Return iterator to end
- [x] `rbegin`: Return reverse iterator to reverse beginning
- [x] `rend`: Return reverse iterator to reverse end

#### Capacity:
- [x] `empty`: Test whether container is empty
- [x] `size`: Return container size
- [ ] `max_size`: Return maximum size

#### Element access:
- [x] `operator[]`: Access element

#### Modifiers:
- [x] `insert`: Insert elements
- [ ] `erase`: Erase elements
- [ ] `swap`: Swap content
- [ ] `clear`: Clear content

#### Observers:
- [x] `key_comp`: Return key comparison object
- [x] `value_comp`: Return value comparison object

#### Operations:
- [x] `find`: Get iterator to element
- [x] `count`: Count elements with a specific key
- [ ] `lower_bound`: Return iterator to lower bound
- [ ] `upper_bound`: Return iterator to upper bound
- [ ] `equal_range`: Get range of equal elements

#### Allocator:
- [x] `get_allocator`: Get allocator

# Stack

## Member functions
- [x] `(constructor)`: Construct stack
- [x] `empty`: Test whether container is empty
- [x] `size`: Return size
- [x] `top`: Access next element
- [x] `push`: Insert element
- [x] `pop`: Remove top element

## Non-member function overloads
- [x] `relational operators`: Relational operators for stack

# Others

## Classes

- [x] `iterators_traits`
- [x] `reverse_iterator`

## Structures

- [x] `enable_if`
- [ ] `is_integral`
- [x] `pair`

## Functions

- [x] `equal`
- [x] `lexicographical_compare`
- [x] `make_pair`
