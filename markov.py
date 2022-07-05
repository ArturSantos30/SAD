from datetime import datetime


# random number generator
def get_initial_seed():
    seed = (datetime.now().second + datetime.now().hour) * datetime.now().microsecond
    return seed**3


def multiply_with_carry():
    seed = get_initial_seed()
    x = 4294957665 * (seed & 4294967295) + (seed >> 32)
    return x%10


#database
def initialize_database(n):
    database = []
    for _ in range(n):
        number = multiply_with_carry()
        if number < 4:
            database.append('A')
        elif number < 7:
            database.append('B')
        else:
            database.append('C')
    return database


#Probability transition matrix
def count_sequences_ocurrences(database, x, y):
    count = 0
    for i in range (len(database)-1):
        if database[i] == x:
            if database[i+1] == y:
                count += 1
    return count


def calculate_probability_for_each_final(database, final):
    probability_final = []
    final_quantity = database[:-1].count(final)
    probability_final.append(count_sequences_ocurrences(database, final, 'A')/final_quantity)
    probability_final.append(count_sequences_ocurrences(database, final, 'B')/final_quantity)
    probability_final.append(count_sequences_ocurrences(database, final, 'C')/final_quantity)
    return probability_final


def create_transition_matrix(database):
    transition_matrix = []
    transition_matrix.append(calculate_probability_for_each_final(database, 'A'))
    transition_matrix.append(calculate_probability_for_each_final(database, 'B'))
    transition_matrix.append(calculate_probability_for_each_final(database, 'C'))
    return transition_matrix


# multiply matrices
def multiply_matrices(X, Y):
    C = [ [0]* len(Y[0]) for _ in range(len(X))]
    for i in range(len(X)):
        for j in range(len(Y[0])):
            for k in range(len(Y)):
                C[i][j] += X[i][k] * Y[k][j]
    return C


#Probability transition matrix
def get_probability_matrix(transition_matrix, multiplications_quantity):
    probability_matrix = transition_matrix.copy()
    for _ in range(multiplications_quantity):
        probability_matrix = multiply_matrices(probability_matrix, transition_matrix.copy())
    return probability_matrix


def print_matrix(matrix):
    for x in matrix:
        print(x)

#main
database = initialize_database(100)
print(database)

print("\nMatriz de Transicao:")
transition_matrix = create_transition_matrix(database)
print_matrix(transition_matrix)

print("\nProbabilidades limite de transicao:")
probability_matrix = get_probability_matrix(transition_matrix, 20)
print_matrix(probability_matrix)
