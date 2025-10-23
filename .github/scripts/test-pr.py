import subprocess
import os
#spend like 4 hours solving this and found it finnaly
#solution must be compiled with static flag and for 64 architecture, static flag ensure that linking will be correct in CLI enviroment
#g++ -static -m64 -o solution.exe solution.cpp

subprocess.run(["git", "fetch", "origin", "main"], check=True,stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
changed_files = subprocess.check_output("git diff --name-only origin/main..HEAD",text=True)  # note to myslef i think this should be changed after exiting for but maybe not lol
changed_files = changed_files.splitlines()
    
def test_file(file_path :str, iterations :int, timeout :int):
    folder = os.path.dirname(file_path)
    solution_file = folder+"/solution.exe"
    generator_file = folder+"/generate_input.py"

    if not os.path.isfile(solution_file) or not os.path.isfile(generator_file):
        print("no solution or generator found for testing in folder path")
        return
    _, file_extension = os.path.splitext(file_path)

    tested_file = file_path

    if file_extension == ".c":
        compilation = ["gcc", file_path, "-o", folder+"/temp.exe"]
        subprocess.run(compilation, check=True)
        tested_file = folder+"/temp.exe"
    elif file_extension == ".cpp":
        compilation = ["g++", file_path, "-o", folder+"/temp.exe"]
        subprocess.run(compilation, check=True)
        tested_file = folder+"/temp.exe"
    else:
        tested_file = "python " + file_path

    for i in range(iterations):
        args = subprocess.check_output("python "+generator_file,text=True)
        args = args+"\n"
        sol_out = subprocess.check_output([solution_file],input=args,text=True,)
        try:
            test_out = subprocess.check_output(tested_file,input=args,text=True,timeout=timeout)
            if sol_out != test_out:
                print(f"Wrong output for input:\n{args}\n\nSolution output was:\n{sol_out}\n\nBut tested file output was\n{test_out}")
                return
            else:
                print(f"{i+1}. Correct")
        except subprocess.TimeoutExpired as e:
            print(f"Process timed out for input:\n{args}")
            return
    if tested_file.endswith(".exe"):
        os.remove(tested_file)


for changed_file in changed_files:
    print(f"********************* TESTS FOR FILE {changed_file} *********************")
    if not changed_file.endswith((".c",".cpp",".py")):
        print(f"{changed_file} is not allowed in PR please contact administrator")
        print("\n\n")
        continue
        #break
    test_file(changed_file,10,5)
    print("\n\n")