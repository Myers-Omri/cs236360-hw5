#include "RegisterStore.hpp"
#include <iostream>
#include <sstream>


string convertInt(int number)
{
	stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}


RegisterStore::RegisterStore() {
	for(int i=0,j=0;i<=TTYPE_REG_MAX,j<=STYPE_REG_MAX;++i,++j)
	{
		string t_reg = "$t";
		string s_reg = "$s";
		_registers.insert(s_reg.append(convertInt(i)));
		_registers.insert(t_reg.append(convertInt(j)));
	}
}

string RegisterStore::GetRegister() {
	if(_registers.empty())
		throw new EmptyStoreException();
	string returnVal = *_registers.begin();
	_registers.erase(returnVal);
	return returnVal;
}

void RegisterStore::ReturnRegister(string registerName) {
	if(!ValidateRegister(registerName))
		throw new InvalidRegisterNameException();
	_registers.insert(registerName);
}

bool RegisterStore::ValidateRegister(string registerName) {
	if (registerName.size() != 3) return false;
	int regNum = registerName[2] - '0';
	return registerName[0] == '$' &&
		   registerName[1] == 's' || registerName[1] == 't' &&
									 regNum <= TTYPE_REG_MAX &&
									 regNum >= 0;
}

int RegisterStore::NumberOfAvailableRegisters() {
	return _registers.size();
}
