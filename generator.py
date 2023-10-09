import random

# Data for test
number_of_tests = 10

num_elements    = 4000
cache_size      = 20

min_test_value  = 1
max_test_value  = 40

# Range for random values
value_range = range(min_test_value, max_test_value) 

# Generate sample data and save it to the corresponding files
for i in range(1, number_of_tests + 1):
    data = [random.choice(value_range) for _ in range(num_elements)]

    with open('./tests/data' + str(i) +'.txt', 'w') as file:
        file.write(str(cache_size) + '\n')
        file.write(str(num_elements) + '\n')
        for value in data:
            file.write(str(value) + '\n')

    print(f"Generated and saved {num_elements} elements in './tests/data.txt'.")