#ifndef MODEL_H
#define MODEL_H

#include<iostream>
#include<string>
#include<vector>

class BaseField{

protected:
    std::string _name;
    bool _no_null = true;

public:
    std::string getName(){return _name;}

    virtual std::string getSql() = 0;
};

class PrimaryField : public BaseField{
    int _value;

public:
    PrimaryField(){
        _name = "ID";
        _value = -1;
    }
    ~PrimaryField() = default;

    int getValue(){return _value;}
    std::string getSql(){
        std::string res = "ID INTEGER PRIMARY KEY AUTOINCREMENT";
        return res;
    }

    void setValue(int value){_value = value;}
};

class IntegerField : public BaseField{
    int _value;
    int _max_length = 0;

public:
    IntegerField(std::string name, int maxLength = 0, bool noNull = true){
        _name.assign(name);
        _value = 0;
        _max_length = maxLength;
        _no_null = noNull;
    }
    ~IntegerField() = default;

    int getValue(){return _value;}
    std::string getSql(){
        std::string res = _name + " INTEGER";
        if(_max_length > 0)
            res.append("(" + std::to_string(_max_length) + ")");
        if(_no_null)
            res.append(" NOT NULL");
        return res;
    }

    void setValue(int value){_value = value;}
};

class BlobField : public BaseField{
    bool _value;

public:
    BlobField(std::string name, bool noNull = true){
        _name.assign(name);
        _value = false;
        _no_null = noNull;
    }
    ~BlobField() = default;

    bool getValue(){return _value;}
    std::string getSql(){
        std::string res = _name + " BLOB";
        if(_no_null)
            res.append(" NOT NULL");
        return res;
    }

    void setValue(bool value){_value = value;}
};

class RealField : public BaseField{
    double _value;
    int _max_length = 0;

public:
    RealField(std::string name, int maxLength = 0, bool noNull = true){
        _name.assign(name);
        _value = 0.0;
        _max_length = maxLength;
        _no_null = noNull;
    }
    ~RealField() = default;

    double getValue(){return _value;}
    std::string getSql(){
        std::string res = _name + " REAL";
        if(_max_length > 0)
            res.append("(" + std::to_string(_max_length) + ")");
        if(_no_null)
            res.append(" NOT NULL");
        return res;
    }
    void setValue(double value){_value = value;}
};

class TextField : public BaseField{
    std::string _value;
    int _max_length = 0;

public:
    TextField(std::string name, int maxLength = 0, bool noNull = true){
        _name.assign(name);
        _value.assign("");
        _max_length = maxLength;
        _no_null = noNull;
    }
    ~TextField() = default;

    std::string getValue(){return _value;}
    std::string getSql(){
        std::string res = _name + " TEXT";
        if(_max_length > 0)
            res.append("(" + std::to_string(_max_length) + ")");
        if(_no_null)
            res.append(" NOT NULL");
        return res;
    }
    void setValue(std::string value){_value.assign(value);}
};

class Table{
protected:
    std::vector<BaseField*> pvf;
    std::string _name;
    bool _is_resighered = false;
    std::string _sql;

public:
    void insertField(BaseField *bf){
        pvf.push_back(bf);
    }

    std::string getSql(){
        std::string res = "CREATE TABLE " + _name + "(" + pvf[0]->getSql();

        for(int i = 1; i < pvf.size(); i++)
            res.append("," + pvf[i]->getSql());

        res.append(");");
        return res;
    }

    void setSql(){
        _sql.assign(getSql());
    }

    void show(){
        std::cout << _sql << std::endl;
    }
};

#endif /* Field_h */
