
if __name__ == "__main__":
    file = open("input", "r")
    lines = file.readlines()
    elves = [0]
    index = 0
    for line in lines:
        if line.replace("\n", "").strip() == "":
            index+=1
            elves.append(0)
        else:
            elves[index] += int(line)

    print(sum(sorted(elves, reverse=True)[:3]))

