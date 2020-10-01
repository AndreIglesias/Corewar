# Team Strategies Best Practices :sparkles:

A good **workflow** positions all of the tools, processes and people for **optimum** *happiness* and *productivity*.

1. Commit **all changes** that complete a task in a **single commit operation** to keep the project **consistent at all time**.

   a. **Review code** and the **code's norme (norminette)** before merging to the shared branch.

   b. Do not merge **incomplete commit**.
   
      * It might build locally in your work area and pass all tests. But it could **break** in another team member’s work area.
      
   c. **Small commits** make it easier for other developers to understand the changes and roll them back if something went wrong.
   
      * **Example**: *fixing two different bugs should produce **two separate commits**.*

   d. A commit is **not a backup** of your current state of your local files, **even if it occurs at the end of the day**.
   
      * No branch should have partial or incomplete changes.

2. **Only** add content or modify the files that **belong to you and to your task**.

   a. With the exception of common files, where everyone can **add function prototypes or crate new structures** (asm.h) but **not make changes** without the agreement of **every developer concerned**.

3. If you need a *change on another developer's code*, **request the changes to the developer** or **explain to him your needs**.

   a. Under **no circumstances** should the code of another developer be modified by someone other than **himself**.
   
   b. The agreed modifications must satisfy the needs of **both developers** and the needs of the **project**.
