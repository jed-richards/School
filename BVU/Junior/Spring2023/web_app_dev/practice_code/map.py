def get_first(s):
    return s.split()[0]

fulls = ['Jed Richards', 'Jason Konz', 'Kaden Sadler']
firsts1 = list(map(get_first, fulls))
firsts2 = list(map(lambda s: s.split()[0], fulls))
print(firsts1)
print(firsts2)

odds = [x for x in range(1, 20, 2)]
print(odds)

name = "Jed Richards"
num = input(f"Hi, {name}. Please enter a number: ")

##################################################################
# var args and keyword args
def make_nested_div(*args, **kwargs):
    s = ""
    for i in range(len(args)-1, -1, -1):
        beg = "<{}>".format(args[i])
        end = "</{}>".format(args[i])
        s = beg + s + end

    attrs = " "
    for key in kwargs:
        attrs += key + '="' + kwargs[key] + '" '

    return "<div{}>".format(attrs) + s + "</div>"

print(make_nested_div())
print(make_nested_div('p', 'span'))
print(make_nested_div('p', id="my-id", sytle="border: 1px;"))
##################################################################


##################################################################
# Decorators
def make_pretty(func):
    def pretty(s):
        print('*'*len(s))
        func(s)
        print('*'*len(s))
    return pretty

@make_pretty
def print_name_tag(s):
    print(s)

print_name_tag('Natalie')
print()
print_name_tag('Georgina')
##################################################################
