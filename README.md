# word_count

To build project, go to wordcountX directory and run:

```bash
cmake . && make
```

To run a project with custom config file:

```bash
./wordcount config.dat
```

or if you want to existing one in a project directory

```bash
./wordcount
```

To run Python script, that checks if consecutive runs return the same maps:

```bash
python3 equality_check.py [num_of_runs]
```

