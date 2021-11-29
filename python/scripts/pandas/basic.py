import pandas as pd
import string

# Basic Data Type
# DataFrame or Serice

# DataFrame
df1 = pd.DataFrame({'col1': list(string.ascii_uppercase),
				   'col2': list(string.ascii_lowercase)})
df2 = pd.DataFrame({'col1': list(string.ascii_uppercase),
				    'col3': list(range(len(string.ascii_lowercase)))})
print(df1.to_string(max_rows=10))

# Operations
# df1.merge(df2, )