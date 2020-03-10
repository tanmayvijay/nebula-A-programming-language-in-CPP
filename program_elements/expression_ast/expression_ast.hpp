#ifndef EXPRESSION_H
#define EXPRESSION_H

#include<string>
#include<iostream>
#include<map>

#include "../../tokenizer/tokenizer.hpp"
#include "../value_type.hpp"



enum NodeType{
	_OPERATOR_NODE_,
	_OPERAND_NODE_
};


class ExpressionAST {
	NodeType type;
//	Token node_data = Token(_OTHER_TOKEN_LITERAL_, "");
	
	public:
		ExpressionAST(NodeType type){
			this->type = type;
//			this->node_data = node_data;
		}
		
		NodeType get_node_type(){
			return this->type;
		}
		
//		Token get_node_data(){
//			return this->node_data;
//		}
		
		virtual void _repr_() = 0;
		
};


enum OperatorPrecedence{
	_OR_,
	_AND_,
	_IS_EQUAL_IS_NOT_EQUAL_,
	_GT_GTE_LT_LTE_,
	_PLUS_MINUS_,
	_MULTIPLY_DIVIDE_MODULUS_,
	_NOT_,
	_SQUARE_BRACKET_,
	_BRACKET_,
};

std::map<std::string, OperatorPrecedence> operator_precendence_mapping {
	{"or", _OR_},
	{"and", _AND_},
	{"==", _IS_EQUAL_IS_NOT_EQUAL_},
	{"!=", _IS_EQUAL_IS_NOT_EQUAL_},
	{">", _GT_GTE_LT_LTE_},
	{">=", _GT_GTE_LT_LTE_},
	{"<", _GT_GTE_LT_LTE_},
	{"<=", _GT_GTE_LT_LTE_},
	{"+", _PLUS_MINUS_},
	{"-", _PLUS_MINUS_},
	{"*", _MULTIPLY_DIVIDE_MODULUS_},
	{"/", _MULTIPLY_DIVIDE_MODULUS_},
	{"%", _MULTIPLY_DIVIDE_MODULUS_},
	{"not", _NOT_},
	{"[", _SQUARE_BRACKET_},
	{"(", _BRACKET_}
	
};


enum OperatorType{
	_UNARY_OP_,
	_BINARY_OP_
};



enum Operator{
	_PLUS_OP_, _MINUS_OP_, _MULTIPLY_OP_, _DIVIDE_OP_, _MODULUS_OP_,
	_AND_OP_, _OR_OP_, _NOT_OP_,
	_EQUAL_OP_, _NOT_EQUAL_OP_, _GT_OP_, _GTE_OP_, _LT_OP_, _LTE_OP_,
	_OPEN_SQUARE_BRACKET_OP_, _OPEN_ROUND_BRACKET_OP_,
}; // add ** (power) to it


std::map<std::string, Operator> string_to_operator_mapping {
	{"or", _OR_OP_},
	{"and", _AND_OP_},
	{"==", _EQUAL_OP_},
	{"!=", _NOT_EQUAL_OP_},
	{">", _GT_OP_},
	{">=", _GTE_OP_},
	{"<", _LT_OP_},
	{"<=", _LTE_OP_},
	{"+", _PLUS_OP_},
	{"-", _MINUS_OP_},
	{"*", _MULTIPLY_OP_},
	{"/", _DIVIDE_OP_},
	{"%", _MODULUS_OP_},
	{"not", _NOT_OP_},
	{"[", _OPEN_SQUARE_BRACKET_OP_},
	{"(", _OPEN_ROUND_BRACKET_OP_}
	
};


class OperatorNode : public ExpressionAST{
	Operator op;
	
	ExpressionAST* left_node = NULL;
	ExpressionAST* right_node = NULL;
	
	OperatorType operator_type;
	
	OperatorPrecedence precedence;
	
//	OperatorType operator_type; // binary or unary
	
	public:
		OperatorNode(std::string op_string) : ExpressionAST(_OPERATOR_NODE_){
			this->op = string_to_operator_mapping.find(op_string)->second;
			this->precedence = operator_precendence_mapping.find(op_string)->second;
			
			if (op == _NOT_OP_)
				this->operator_type = _UNARY_OP_;
			else
				this->operator_type = _BINARY_OP_;
		}
		
		Operator get_operator(){
			return this->op; 
		}
		
		OperatorPrecedence get_operator_precedence(){
			return this->precedence;
		}
		
		OperatorType get_operator_type(){
			return this->operator_type;
		}

		
		ExpressionAST* get_left_node(){
			return this->left_node;
		}
		
		ExpressionAST* get_right_node(){
			return this->right_node;
		}
		
		void set_left_node(ExpressionAST* node){
			this->left_node = node;
		}
		
		void set_right_node(ExpressionAST* node){
			this->right_node = node;
		}
		
		
		void _repr_(){
			std::cout << " [ ";
			
			if (this->left_node)
				this->left_node->_repr_();
			
			std::cout << " " << this->op << " ";
			
			this->right_node->_repr_();
			
			std::cout << " ] ";
		}
			
};

#include "../symbol_table/symbol_table.hpp"

class OperandNodeWithSymbol : public ExpressionAST{
//	ValueType operand_type;
//	ExpressionAST* operand_value_expression;
	Symbol* symbol;
	public:
//		OperandNodeWithExpression(ValueType operand_type, ExpressionAST* operand_value) : ExpressionAST(_OPERAND_NODE_){
//			this->operand_type = operand_type;
//			this->operand_value_expression = operand_value;
//		}

		OperandNodeWithSymbol(Symbol* symbol) : ExpressionAST(_OPERAND_NODE_){
			this->symbol = symbol;
		}
		
		void _repr_(){
			std::cout << " [ ";
			std::cout << symbol->get_symbol_name();
			std::cout << " ] ";
		}
		
		
		// evaluate frther calls the expression's evaluate;
	
};



std::map<ValueType, std::string> ValueType_to_default_value_mapping {
	{_NONE_, "N/A"},
	{_INTEGER_, "0"},
	{_DECIMAL_, "0.0"},
	{_STRING_, ""},
	{_BOOLEAN_, "False"},
	{_CUSTOM_, ""}
};



class OperandNodeWithConstant : public ExpressionAST{
	ValueType operand_type;
	std::string operand_value;
	public:
//		OperandNodeFinal(ValueType operand_type, std::string operand_value) : ExpressionAST(_OPERAND_NODE_){
//			this->operand_type = operand_type;
//			this->operand_value = operand_value;
//		}

		OperandNodeWithConstant(ValueType operand_type, std::string operand_value) : ExpressionAST(_OPERAND_NODE_){
			this->operand_type = operand_type;
			this->operand_value = operand_value;
		}
		
		OperandNodeWithConstant(ValueType operand_type) : ExpressionAST(_OPERAND_NODE_){
			this->operand_type = operand_type;
			this->operand_value = ValueType_to_default_value_mapping.find(operand_type)->second;
		}
		
		void _repr_(){
			std::cout << operand_value;
		}
		
		// evaluate simply returns string value	
};


#endif
