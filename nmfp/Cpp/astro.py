import numpy as np
import matplotlib.pyplot as plt

import scipy.misc
from scipy import misc

from skimage import color, data, restoration

rgb_arr = misc.imread('one.jpg')

astro = color.rgb2gray(rgb_arr)

from scipy.signal import convolve2d as conv2

fig, ax = plt.subplots(nrows=1, ncols=2, figsize=(15, 7),
                       sharex=True, sharey=True)
plt.gray()

ax[0].imshow(astro)
ax[0].axis('off')
ax[0].set_title('Orig Gray')

psf = np.ones((5, 5)) / 25
astro2 = conv2(astro, psf, 'same')
astro2 += (0.1)*astro2.std()*np.random.standard_normal(astro2.shape)

deconvolved, _ = restoration.unsupervised_wiener(astro2, psf)

#ax[0].imshow(astro, vmin=deconvolved.min(), vmax=deconvolved.max())
#ax[1].imshow(astro)
#ax[1].axis('off')
#ax[1].set_title('Data')

ax[1].imshow(deconvolved)
ax[1].axis('off')
ax[1].set_title('Self tuned restoration')

fig.tight_layout()

plt.show()
