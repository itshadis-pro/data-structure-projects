# P1 Report

Name: Hadi Almarzooq

Run `make run` and copy the ratios from the last column.

| n (pushes) | copies | copies / pushes |
|---|---|---|
| 1000 | 1023 | 1.023 |
| 10000 | 16383 | 1.638 |
| 100000 | 131071 | 1.311 |


In one or two sentences, explain why copies / pushes stays below 2 for every n. Hint: which pushes trigger a growth, and how many elements does each growth copy?

The copies/pushes ratio stays below 2 because we double the capacity during each growth phase. Copying N elments guaruantees exactly N 'free' pushes before the stack needs to grow again, ensuring the total number of copies never exceeds twice the number of pushes.

// used AI to get help tutoring writing test cases and brainstorming this 2 sentences report. 