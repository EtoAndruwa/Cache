import random

# Number of elements
num_elements = 200

# Range for random values
value_range = range(1, 5)

# Generate random data
data = [random.choice(value_range) for _ in range(num_elements)]

# Save the data to a file
with open('./tests/data4.txt', 'w') as file:
    for value in data:
        file.write(str(value) + '\n')

print(f"Generated and saved {num_elements} elements in './tests/data4.txt'.")