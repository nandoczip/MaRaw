import os


def main():
    paths = ('pre/header', 'pre/src')
    
    exts = ('hp', 'cp')

    for fn in os.listdir(paths[0]):
        name, _ = fn.split('.')
        fin_data = ''
        
        for i, ext in enumerate(exts):
            with open(f'{paths[i]}/{name}.{ext}') as file:
                data = file.read()

            a = False
            until = False

            for line in data.split('\n'):
                if until:
                    if line == '':
                        fin_data += '\n'
                        continue
                    until = False

                if '#startdef' in line:
                    a = True
                    until = True
                    continue

                if '#enddef' in line:
                    a = False
                    continue
                
                if '//' in line:
                    continue

                if a:
                    fin_data += f'{line} \\\n'
                else:
                    fin_data += f'{line}\n'

            with open(f'{paths[i].replace("pre/", "")}/{name}.{ext.rstrip('p')}', 'w') as file:
                file.write(fin_data)


if __name__ == '__main__':
    main()
