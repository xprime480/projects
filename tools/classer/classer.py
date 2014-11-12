#!/usr/bin/python3

def merge_groups(groups) :
    new_groups = []
    for group in groups :
        if len(group) == 0 :
            continue

        file_name = group[0][0]
        file_line = int(group[0][1])
        texts = [g[2] for g in group]
        text = ' '.join(texts)
        new_groups.append((file_name, file_line, text))

    return new_groups
    

def get_items_from_file(file_name) :
    with open(file_name) as f :
        data = f.readlines()

    import scanner
    scanner = scanner.Scanner(data)
    data = scanner.group()
    data = merge_groups(data)

    return data
        
def get_items(file_names) :
    items = []
    for file_name in file_names :
        new_items = get_items_from_file(file_name)
        items.extend(new_items)
    return items

def get_file_names() :
    import sys
    return sys.argv[1:]

def parse_specs(specs) :
    import class_decl_scanner
    scanner = class_decl_scanner.ClassDeclScanner()
    results = []
    for x in specs :
        r = scanner.scan(x)
        if r : 
            results.append(r)
        else :
            print (x)
            return []
    return results

if __name__ == '__main__' :
    file_names = get_file_names()
    items = get_items(file_names)
    specs = parse_specs(items)

    print (specs[:10])
    print ('There are %d candidates.' % len(specs))

