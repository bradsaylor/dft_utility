| Variable | Meaning                                 | Description                                                                                                          |
| -------- | --------------------------------------- | -------------------------------------------------------------------------------------------------------------------- |
| `$@`     | **Target**                              | The name of the file that is the target of the rule.                                                                 |
| `$<`     | **First prerequisite**                  | The name of the first dependency (prerequisite) in the rule.                                                         |
| `$^`     | **All prerequisites**                   | All dependencies of the rule, with duplicates removed.                                                               |
| `$+`     | **All prerequisites (with duplicates)** | Like `$^`, but preserves duplicates and order.                                                                       |
| `$?`     | **Changed prerequisites**               | All prerequisites that are newer than the target (i.e. that have changed).                                           |
| `$*`     | **Stem**                                | The stem of a pattern rule target — the part that matched the `%`. Useful for inferring file names in pattern rules. |
| `$$`     | **Literal `$`**                         | Use this when you want a literal dollar sign (`$`) in a shell command.                                               |
