ss = 0
for i in range(1,101):
    ss += i**4


print(sum([x**4 for x in range(1,101)]))

l = 100**5/5
h = 101**5/5
a = (l+h)/2

e = (ss-a)/ss

f = 100**5/5 + 100**4/2 + 100**3/3 -100/30

print(f"Exact Answer = {ss}")
print()
print(f"Low approximation = {l}")
print(f"High approximation = {h}")
print(f"Avg approximation = {a}")
print(f"Percentage Error = {e*100:.3f}%")
print()
print(f"Faulhaber Approximation = {f}")
