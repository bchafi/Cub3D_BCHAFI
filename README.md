# Roadmap for `main()` in Cub3D Parsing

---

## Check arguments:

* **Check arguments** → exactly `2`

  * ❌ If not → print error `"** Uncomplite Argument **"` and exit.

---

## 📘 `check_file` — File Validation for Cub3D

```c
int check_file(char *arg);
```
---

This function ensures the program receives a **valid `.cub` map file** before parsing.
It performs **3 main checks**:
  - file extension.
  - directory check.
  - file existence.

* **Input:** `arg` → path to the file given as program argument.
* **Output:** file descriptor (`fd`) ready for reading.
* **Failure:** writes error message to `stderr` and exits with code `1001` or `1002`.

---

* File must end with **`.cub`**.
* If not → print error and exit `1001`.
* Check if Path is a Directory
```c
  fd = open(arg, O_DIRECTORY, 666);
``` 
* If `open()` succeeds in directory mode → path is a **folder, not a file**.
* Close it, print error, exit `1002`.
* 3. Check File Existence & Permissions
```c
fd = open(arg, O_RDWR, 666);
```
* Open file in **read/write mode**.
* If it fails → file does not exist or permission denied.
* Print error, exit `1002`.
* ⚠️ Error Codes
 ***1001** → Invalid file extension (not `.cub`).*
 ***1002** → File is a directory, missing, or unreadable.*

---

## 🌟 `get_full_file()` – Roadmap / Cheat Sheet

| Step | Action                            | Notes                                                                      |
| ---- | --------------------------------- | -------------------------------------------------------------------------- |
| 1️⃣  | **Read file once to count lines** | `file = get_next_line(fd)`; increment `i` until EOF; free each line        |
| 2️⃣  | **Allocate 2D array**             | `file2D = malloc(sizeof(char*) * (i + 1))`; size = line count + 1 for NULL |
| 3️⃣  | **Reopen file**                   | `close(fd)` then `fd = open(arg, O_RDONLY)` to start reading lines again   |
| 4️⃣  | **Fill 2D array**                 | `file2D[i++] = file` for each line read with `get_next_line`               |
| 5️⃣  | **Null-terminate array**          | `file2D[i] = NULL`                                                         |
| 6️⃣  | **Set line count**                | `vars->len_lines = i`                                                     |
| 7️⃣  | **Return array**                  | Return `file2D` (caller must free)                                         |
| ⚠️   | **Error Handling**                | Empty file → print error + close fd; malloc fail → close fd + return NULL  |

---

## 🗺️ Roadmap for `check_sides_tex`

---

### 🎯 **Goal**

Parse the `.cub` file lines and:

* Collect **texture paths** (`NO`, `SO`, `WE`, `EA`).
* Collect **colors** (`F`, `C`).
* Prevent **duplicates**.
* Store them inside `vars->s_tex` and `vars->s_color`.
=> * For every `file_line[i]`
* Check duplicates with `is_seeing(..., flag=1)`.
* If duplicate → ❌ error → free memory + return NULL.
---

### 🏗️ **Steps**


##### 🔹 **If the line `NO`, `SO`, `WE`, `EA` , `F` , `C`**

* Check duplicates with `is_seeing(..., flag=1)`.
* If duplicate → ❌ error → free memory + return NULL.
* Else → ✅ save path:
  ```c
    vars->s_tex[vars->tx_count++] = ft_strdup(file_line[i] + 3);
  ```
  *(skip `"NO "` → keep only the file path)*

* Check duplicates with `is_seeing(..., flag=0)`.
* If duplicate → ❌ error → free memory + return NULL.
* Else → ✅ save RGB:

  ```c
  vars->s_color[vars->c_count++] = ft_strdup(file_line[i] + 2);
  ```
  *(skip `"F "` or `"C "` → keep only the RGB values)*
---

#### 3️⃣ **After the loop**

* Null-terminate arrays

---

### 🎨 Visual Summary

* 🟦 **Textures** → `vars->s_tex = { "wall_north.png", "wall_south.png", "wall_west.png", "wall_east.png", NULL }`
* 🟩 **Colors** → `vars->s_color = { "220,100,0", "225,30,0", NULL }`
* 🔴 **Errors handled**:

  * Duplicate texture direction.
  * Duplicate floor/ceiling color.

---




> string after the keyword of the color
> slice it by split
> check lenght must == 3 args.
> take every part of argb:
  - trimed it by removing ` \n\t`











- The map must be closed/surrounded by walls -> return an error.


