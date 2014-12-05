### Lifecycle Methods

 - default-or-argument-bearing 'user' constructors

 - declaration-or-deletion-of-copy-contructor
 - declaration-or-deletetion-of-move-constructor

 - declaration-or-deletion-of-copy-assignment-operator
 - declaration-or-deletion-of-move-assignment-operator

 - declaration-of-dtor

### Headers

 - License
 - Prelude
 - System Headers `<>`
 - Driver Headers `""`
 - Open Namespace mongo
 - Open Namespace driver
 -    Code
 - Close Namespace driver
 - Close Namespace mongo
 - Postlude

### Class Declarations

Guidelines:

 - Blank line at beginning and end of class declaration
 - Public section up top / private at bottom
 - Lifecycle methods first (see rules above)
 - Private Member Ordering
   - Friendships
   - Private Constructors
   - Private Methods
   - Private Variables

Example:
```cpp
class foo {

    public:
      foo();

      foo(foo&& other) noexcept;
      foo& operator=(foo&& other) noexcept;

      ~foo();

    private:
      friend baz;

      class impl;
      std::unique_ptr<impl> _impl;

};
```

### Inlines
 - Define outside of class declaration
 - Specify inline keyword in declaration and definition (for clarity)

### Relational Operators
 - Prefer to use free functions
