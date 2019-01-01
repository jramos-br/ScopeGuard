# ScopeGuard
Yet another ScopeGuard class for C++

## How to use

1. Include "ScopeExit.hpp"
2. Use SCOPE_EXIT or SCOPE_EXIT_DECL macro and pass a callback function or
   a lambda expression to be called at scope exit.
3. To avoid the callback execution use the Dismiss function. To access the
   defined ScopeExit object and call its Dismiss function use the
   SCOPE_EXIT_DECL macro.

## Use case #1

Release dynamically allocated data before the function returns,
even if an exception occurs.

Using a try-catch block:
```c++
void Foo()
{
    std::vector<int>* v = new std::vector<int>(2);
    try
    {
        // more stuff...
        int i = v->at(2); // Oops!
        // even more stuff...
    }
    catch (...)
    {
        delete v;
        throw;
    }
    delete v;
}
```

Using the SCOPE_EXIT macro:
```c++
#include "ScopeExit.hpp"

void Foo()
{
    std::vector<int>* v = new std::vector<int>(2);
    SCOPE_EXIT([v] { delete v; });
    // more stuff...
    int i = v->at(2); // Oops!
    // even more stuff...
} // delete v is executed before Foo returns,
  // even if Foo throws an exception.
```

## Use case #2

Begin a database transaction and rollback it if an exception occurs.
After a successful commit there is no need to rollback.

Using a try-catch block:
```c++
void Foo(DbContext* ctx)
{
    ctx->BeginTransaction();
    try
    {
        // more stuff...
        ctx->Commit();
    }
    catch (...)
    {
        ctx->Rollback();
        throw;
    }
    // even more stuff...
}
```

Using the SCOPE_EXIT_DECL macro:
```c++
#include "ScopeExit.hpp"

void Foo(DbContext* ctx)
{
    ctx->BeginTransaction();
    SCOPE_EXIT_DECL(sg, [ctx] { ctx->Rollback(); });
    // more stuff...
    ctx->Commit();
    sg.Dismiss();
    // even more stuff...
} // Rollback is called before Foo returns even if Foo
  // throws an exception (before Dismiss is called). After
  // the Dismiss call, sg will not call Rollback anymore.
```

## License

The ScopeExit class is free software, licensed under the terms of the MIT License as published by the [Open Source Initiative](http://opensource.org).
It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.
See the file [LICENSE](/LICENSE) for more details.
If you don't find it, please see the MIT License template at
http://opensource.org/licenses/MIT.

Copyright (C) 2018 Jorge Ramos https://github.com/jramos-br
