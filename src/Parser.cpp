#include "Parser.hpp"

std::string Parser::trim(const std::string &string){
    size_t start = string.find_first_not_of(" ");
    size_t end = string.find_last_not_of(" ");
    return (start == std::string::npos) ?  "" : string.substr(start, end - start + 1) ; 
}
std::string Parser::parse_params(const std::string &str){
    size_t open = str.find('(');
    size_t close = str.find(')');
    if(open != std::string::npos && close != std::string::npos && close > open ){
        return str.substr(open+1, close - open - 1);
    }
    return "";
}
int Parser::str_to_num(const std::string &str){
    signed int num = 0;
    bool neg = (str[0] == '-');
    for(int i = 0+ neg; i < str.size(); i++){
        num += pow(10,(str.size()-1 - i)) * ((int)str[i] - 48);
    }
    return neg  ? -num : num;
}
std::string Parser::find_file(){
    std::string filename;
    constexpr char dir[] = "scene";
    if(!fs::exists(dir)){
        std::cerr << "directory : \"" << *dir << "\" does not exist \n ";
        return "";
    }
    for(const auto &entry : fs::directory_iterator(dir)){
        if(entry.is_regular_file() && entry.path().extension() == ".sc"){
            filename = entry.path().string();
            return filename;
        }
    }
    return "";
}

Parser::Parser(){
    this->source_file = this->find_file();
    this->file = std::fstream(source_file);
}

std::vector<SceneObject*> Parser::parse(){
    std::vector<SceneObject*> objects;
    std::string params = "";
    std::vector<double> attributes;
    std::string num = "";
    while(std::getline(file,params)){
        params = trim(params);
        if(params.find("//") == 0){
            continue;
        }
        bool spring = (params.find("spring") == 0) ;
        params = parse_params(params);
        for(int i = 0; i < params.size(); i++){
            if(params[i] >= '0' && params[i] <= '9'){
                if( i > 0 && params[i-1] == '-' ) num = '-';
                num += params[i];
            }
            else{
                if(!num.empty()){
                    attributes.push_back(str_to_num(num));
                    num = "";
                }
            }
        }
        if(!num.empty()){
            attributes.push_back(str_to_num(num));
            num = "";
        }
        
        if(spring){
            if(!dynamic_cast<Circle*>(objects.back())){
                std::cerr << "no Circle object already initiated before Spring object\n";
            }
            else{
                Circle *ptr = dynamic_cast<Circle*>(objects.back());
                objects.push_back(new Spring(Vec2(attributes[0],attributes[1]),ptr,attributes[2],attributes[3]));
            }
        }
        
        else if(!spring && attributes.size() == 8){
            objects.push_back(new Circle(Vec2(attributes[0],attributes[1]),Vec2(attributes[2],attributes[3]),Vec2(attributes[4],attributes[5]),attributes[6],attributes[7]));
        }

        attributes.clear();
        attributes.shrink_to_fit();
    }
    return objects;
}