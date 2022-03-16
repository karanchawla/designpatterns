## Strategy Pattern

### Intent
To define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets algorithm vary independently from the clients that use it. 

### Applicability 
Use Strategy pattern when —
1. Many related classes differ only in their behavior. Strategy provides a way to configure a class with one of many behaviors. 
2. You need different variants of an algorithm. For e.g., you might define algorithms that reflect different space/time tradeoffs. Strategies can be used when these variants are implemented as a class hierarchy of algorithms. 
3. A class defines many behaviors and these appear as mulitple conditional statements in its operations. 

