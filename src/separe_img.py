import cv2
import matplotlib.pyplot as plt
import numpy as np

def obtener_canal_monocromatico(imagen, canal, nombre_archivo):
    i=0
    # Carga la imagen en modo BGR
    img = cv2.imread(imagen)

    # Extrae el canal especificado
    canal_img = img[:, :, canal]

    # Guarda el canal monocromático en un archivo de texto
    np.savetxt(nombre_archivo, canal_img, fmt='%d')

    if(i == 0):

        dimensiones = canal_img.shape

        # Guarda las dimensiones en un archivo de texto
        with open('dimensiones.txt', 'w') as f:
            f.write(f'{dimensiones[1]} {dimensiones[0]}')
        
        i=i+1

    return canal_img

ruta_imagen = '../imgs/sentinel.png'

canal_r = obtener_canal_monocromatico(ruta_imagen, 2, 'canal_r.txt')  # Canal R

canal_g = obtener_canal_monocromatico(ruta_imagen, 1, 'canal_g.txt')  # Canal G

canal_b = obtener_canal_monocromatico(ruta_imagen, 0, 'canal_b.txt')  # Canal B


# import cv2
# import matplotlib.pyplot as plt

# def obtener_canal_monocromatico(imagen, canal):
#     # Carga la imagen en modo BGR
#     img = cv2.imread(imagen)

#     # Extrae el canal especificado
#     canal_img = img[:, :, canal]

#     return canal_img


# ruta_imagen = '../imgs/sentinel.png'

# canal_r = obtener_canal_monocromatico(ruta_imagen, 2)  # Canal R

# canal_g = obtener_canal_monocromatico(ruta_imagen, 1)  # Canal G

# canal_b = obtener_canal_monocromatico(ruta_imagen, 0)  # Canal B


# fig, axs = plt.subplots(1, 3, figsize=(12, 4))

# # Muestra el canal R monocromático
# axs[0].imshow(canal_r, cmap='gray')
# axs[0].set_title('Canal R')

# # Muestra el canal G monocromático
# axs[1].imshow(canal_g, cmap='gray')
# axs[1].set_title('Canal G')

# # Muestra el canal B monocromático
# axs[2].imshow(canal_b, cmap='gray')
# axs[2].set_title('Canal B')

# plt.tight_layout()

# plt.show()


