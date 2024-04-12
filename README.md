## Execute the following commands to reproduce the error

```bash
# Clone the repository
git clone https://github.com/gsc74/test_ksort.git
cd test_ksort
make

# Execute
./sort
```

### Output
```bash
Time taken for radix sort: 28 ms
Time taken for std::stable_sort: 11 ms
Error: a[512000] = {512, 999} != c[512000] = {512, 0}
```
