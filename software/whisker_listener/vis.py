import pandas as pd
import matplotlib.pyplot as plt
from io import StringIO



# Read the data into a DataFrame
date_format = "%Y-%m-%d_%H:%M:%S.%f"
df = pd.read_csv('p240_test.csv', parse_dates=['timestamp'], date_parser=lambda x: pd.to_datetime(x, format=date_format))

# Plot the data
plt.figure(figsize=(10, 5))
plt.plot(df['timestamp'].to_numpy(), df['AY'].to_numpy(), marker='o')
plt.title('Value over Time')
plt.xlabel('Timestamp')
plt.ylabel('Value')
plt.xticks(rotation=45)
plt.grid(True)
plt.tight_layout()
plt.show()
