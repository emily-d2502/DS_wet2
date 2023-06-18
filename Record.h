#ifndef RECORD_H
#define RECORD_H

class Record {
public:
    explicit Record(int r_id);
    Record();

    Record(const Record& other)            = default;
    Record& operator=(const Record& other) = default;
    ~Record()                              = default;

    int id() const;
    int copies() const;
    int buys() const;


    void setColumn(int Column);
    int getColumn() const;


    void setCopies(int copies);

    void setHeight(int height);

    int getHeight() const;


    void buy();
    void zeroBuys();


private:
    int _id;
    int _copies;
    int _buys;
    int _stackHeight;
    int _column;
};

#endif
