def main():  
    while True:
        f = open("/tmp/ECGFromServer", "r")
        while True:
           testline = f.readline()
           if len(testline) ==0:
               break # EOF
           print testline
        f.close()
                                      
if __name__ == "__main__":  
    main()  
