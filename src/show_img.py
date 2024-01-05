import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# Leer los archivos binarios con las matrices
with open("filtered_r.bin", "rb") as file_r:
    dims = np.fromfile(file_r, dtype=np.int32, count=2)
    matrix_r = np.fromfile(file_r, dtype=np.float32).reshape(dims)
    
with open("filtered_g.bin", "rb") as file_g:
    dims = np.fromfile(file_g, dtype=np.int32, count=2)
    matrix_g = np.fromfile(file_g, dtype=np.float32).reshape(dims)

with open("filtered_b.bin", "rb") as file_b:
    dims = np.fromfile(file_b, dtype=np.int32, count=2)
    matrix_b = np.fromfile(file_b, dtype=np.float32).reshape(dims)

    
result_matrix = matrix_r + matrix_g + matrix_b

# mpimg.imsave("result.png", result_matrix, cmap='gray')  # Usar cmap='gray' si las matrices son en escala de grises

# Visualizar la imagen resultante
plt.imshow(result_matrix, cmap='gray')  
plt.axis('off')  
plt.show()

















