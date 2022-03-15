## Principles for object oriented design

|     |                     |
|:---:|:--------------------|
|  S  |Single Responsibility|
|  O  |Open-close           |
|  L  |Liskov substitution  |
|  I  |Interface segregation|
|  D  |Dependency inversion |

## Single Responsibility

A class should have a single reason to change. - **Separation of Concerns** 

## Open-Closed

The object should be **open for extension and closed for modification**.

- We want to avoid modifying code that already works.
- However, we must be able to easily extend the object by using inheritance.

## Liskov Substitution

Sub-types should be substitutable by their base types.

- Methods designed to work on the `Derived` class should keep working when a `Base` instance is used.

## Interface Segregation

Avoid putting too much into a single interface. Don't force implementers to implement really large interfaces.

- Partial implementers contain dummy methods and extra code.
- Partial implementers give a wrong API to the user.

## Dependency Inversion

1. High-level modules should not depend on low-level modules. Both should depend on abstractions.
2. Abstractions should not depend on details. Details should depend on abstractions.

Prefer depending on abstractions (abstract and interfaces) rather than specific classes. *Avoid depending on the implementation details*.