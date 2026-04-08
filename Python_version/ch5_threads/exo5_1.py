import threading

def print_tab(t): print(t)
threading.Thread(target=print_tab, args=([1, 2, 3, 4],)).start()
