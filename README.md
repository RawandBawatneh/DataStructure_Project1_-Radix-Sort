# 📚 COMP2421 - Data Structures and Algorithms (Spring 2023/2024)

## 📝 Project #1: Radix Sort with Linked Lists

### 🌟 Project Description

In this project, we implement an application of **Radix Sort** using **doubly linked lists**. The goal is to build a 2-level hierarchy for Palestinian districts and towns, sorting the districts alphabetically using Radix Sort. Additionally, towns within each district will be sorted based on population in ascending order.

The input for the program will be a file containing district and town details, and the output will be a sorted file, showing districts with their total population and a list of towns and populations within each district.

---

### 📂 Input File Format

The input file (`districts.txt`) will contain an unspecified number of lines, each representing:
- 🏙️ **District Name**
- 🏘️ **Town Name**
- 👥 **Town Population**

Fields are separated by the pipe symbol (`|`). Example of input format:

Hebron | Dura | 100000
Hebron | Halhul | 40000
Jenin | Jaba | 7000
Jenin | Yabad | 31000
Jenin | Jenin | 92000
Gaza | Jabalia | 20000
Gaza | Beit Hanoon | 50000

---

### 📊 Output File Format

The output file (`sorted_districts.txt`) will list the districts alphabetically, along with their total population. Each district will be followed by a list of its towns and their respective populations. Example:

🌍 Gaza District, Population = 70000
🏘️ Beit Hanoon, 50000
🏘️ Jabalia, 20000

🌍 Hebron District, Population = 140000
🏘️ Halhul, 40000
🏘️ Dura, 100000

🌍 Jenin District, Population = 130000
🏘️ Jaba, 7000
🏘️ Yabad, 31000
🏘️ Jenin, 92000

---

### 🛠️ Program Features

Your application will support the following features via a menu interface:

1. 📂 **Load Input File**: Load district and town data from `districts.txt`.
2. 📋 **Display Unsorted Data**: Print the loaded information as it appears in the input file.
3. 🔠 **Sort Districts**: Sort the districts alphabetically using Radix Sort.
4. 📈 **Sort Towns by Population**: Sort the towns within each district by population in ascending order.
5. 🖨️ **Display Sorted Data**: Print the sorted districts and towns.
6. ➕ **Add New District**: Add a new district to the sorted list and re-sort the districts.
7. 🏘️ **Add New Town**: Add a new town to a specified district.
8. ❌ **Delete Town**: Remove a town from a district.
9. 🏙️ **Delete District**: Remove a district and all of its towns.
10. 📊 **Population Statistics**: Calculate the total population of Palestine, the town with the largest population, and the town with the smallest population.
11. 🏷️ **Display District Population**: Print only the district names with their total populations.
12. 📝 **Update Town Population**: Modify the population of a town.
13. 💾 **Save Data**: Save the sorted data to `sorted_districts.txt`.
14. 🚪 **Exit**: Close the program.

---
