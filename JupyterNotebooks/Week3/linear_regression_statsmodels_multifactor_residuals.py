import matplotlib.pyplot as plt
import pandas as pd
import statsmodels.formula.api as smf

include_newspaper = False

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
ax.hist(advert['resid1'], color = "blue", ec="white", bins=50, label='Sales ~ TV')
ax.hist(advert['resid2'], color = "yellow", ec="blue", bins=50, label='Sales ~ TV + Radio')
if include_newspaper:
    ax.hist(advert['resid3'], color = "lightblue", ec="yellow", bins=50, label='Sales ~ TV + Radio + Newspaper')


print("Residuals Summary:")
print(f"TV: {advert['resid1'].mean():.4f} +/- {advert['resid1'].std():.4f}")
print(f"TV + Radio: {advert['resid2'].mean():.4f} +/- {advert['resid2'].std():.4f}")
if include_newspaper:
    print(f"TV + Radio + Newspaper: {advert['resid3'].mean():.4f} +/- {advert['resid3'].std():.4f}")


plt.legend()
plt.show()