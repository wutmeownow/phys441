import matplotlib.pyplot as plt
import pandas as pd
import statsmodels.formula.api as smf

# Get the data
advert = pd.read_csv('advertising.csv')
print(advert.head())

fig, ax = plt.subplots(1, figsize=(8,8))
fig.suptitle("Effects of Advertising on Sales - Residual Plot")

# Fit a linear regression models to different combinations of parameters
model1 = smf.ols('Sales ~ TV', data=advert)
model1 = model1.fit()
model2 = smf.ols('Sales ~ TV + Radio', data=advert)
model2 = model2.fit()
model3 = smf.ols('Sales ~ TV + Radio + Newspaper', data=advert)
model3 = model3.fit()

# View model summary
print(model3.summary())

# Predict values
sales_pred1 = model1.predict()
advert['resid1'] = advert['Sales'] - sales_pred1
sales_pred2 = model2.predict()
advert['resid2'] = advert['Sales'] - sales_pred2
sales_pred3 = model3.predict()
advert['resid3'] = advert['Sales'] - sales_pred3

# Plot regression against actual data
ax.hist(advert['resid1'], color = "blue", ec="white", bins=50, label='Sales ~ TV')           # histogram of residuals
ax.hist(advert['resid2'], color = "yellow", ec="blue", bins=50, label='Sales ~ TV + Radio')           # histogram of residuals
#ax.hist(advert['resid3'], color = "lightblue", ec="yellow", bins=50, label='Sales ~ TV + Radio + Newspaper')


print("Residuals Summary:")
print("Mean and Standard Deviation of Residuals")
print(advert['resid1'].mean(), advert['resid2'].mean(), advert['resid3'].mean())
print(advert['resid1'].std(), advert['resid2'].std(), advert['resid3'].std())


plt.legend()
plt.show()