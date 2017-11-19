import os
import sys

class Table():
    def __init__(self, name, attributes):
        self.name = name
        self.attrCount = len(attributes)
        self.attributes = attributes
        self.sumLen = 0
        for i in range(self.attrCount):
            attrType = self.attributes[i][1]
            if(attrType == 'INTEGER'):
                self.attributes[i][2] = 24
            if(attrType == 'FLOAT'):
                self.attributes[i][2] = 24
            if(attrType == 'DATE'):
                self.attributes[i][2] = 12
            if(attrType == 'CHAR' or attrType == 'VARCHAR'):
                self.attributes[i][2] = int(self.attributes[i][2]) + 1
            self.sumLen = self.sumLen + self.attributes[i][2]
    def encode(self, line):
        out = ''
        values = line.split("|")
        cur_len = 0
        for i in range(self.attrCount):
            value = values[i]
            attrLen = self.attributes[i][2]
            cur_len = cur_len + attrLen
            out = out + value + '\0'
            out = out.ljust(cur_len, '*')
        out = out.ljust(512, '*')
        return bytes(out)
if __name__ == '__main__':
    fd_format = open('benchmark_format')
    while True:
        line_format = fd_format.readline().strip()
        if(line_format == ''):
            fd_format.close()
            break
        tmp_list = line_format.split(" ")
        tableName = tmp_list.pop(0)
        tmp_list.pop(0)
        attributes = []
        attrCount = len(tmp_list)/3
        for i in range(attrCount):
            b = 3 * i
            e = 3 * i + 3
            attributes.append(tmp_list[b:e])
        table = Table(tableName, attributes)
        fd_data = open(tableName, "r")
        fd_out = open(tableName + '.data', "w")
        while True:
            line_data = fd_data.readline().strip()
            if(line_data == ''):
                fd_data.close()
                fd_out.close()
                break
            fd_out.write(table.encode(line_data))
