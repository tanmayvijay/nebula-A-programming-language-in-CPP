#ifndef EXPRESSION_H
#define EXPRESSION_H

#include<string>
#include<iostream>
#include<map>

#include "../../tokenizer/tokenizer.hpp"
#include "../value_type.hpp"
#include "../../exceptions/nebula_exceptions.hpp"



enum NodeType{
	_OPERATOR_NODE_,
	_OPERAND_NODE_
};


class ExpressionAST {
	NodeType type;
	
	public:
		ExpressionAST(NodeType type){
			this->type = type;
		}
		
		NodeType get_node_type(){
			return this->type;
		}
		
//		Token get_node_data(){
//			return this->node_data;
//		}
		
		virtual void _repr_() = 0;
		
		virtual ValueType determine_final_type() = 0;
		
};


enum OperatorPrecedence{
	_OR_,
	_AND_,
	_IS_EQUAL_IS_NOT_EQUAL_,
	_GT_GTE_LT_LTE_,
	_PLUS_MINUS_,
	_MULTIPLY_DIVIDE_MODULUS_,
	_UNARY_MINUS_NOT_,
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
	{"not", _UNARY_MINUS_NOT_},
	{"[", _SQUARE_BRACKET_},
	{"(", _BRACKET_}
	
};


enum OperatorType{
	_UNARY_OP_,
	_BINARY_OP_, 
	_BRACKET_OP_
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
		OperatorNode(std::string op_string, OperatorType op_type) : ExpressionAST(_OPERATOR_NODE_){
			this->op = string_to_operator_mapping.find(op_string)->second;
			this->operator_type = op_type;
			this->precedence = operator_precendence_mapping.find(op_string)->second;
//			std::cout << this->precedence;
			if (this->operator_type == _UNARY_OP_) this->precedence = _UNARY_MINUS_NOT_;
//			std::cout<< this->precedence;
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
		
		ValueType determine_final_type(){ // this automatically does check semantic of the expression
			
			ValueType r_type = this->right_node->determine_final_type();
			
			if ( !this->left_node && this->op == _MINUS_OP_){
				if (r_type == _INTEGER_ || r_type == _DECIMAL_) return r_type;
			}
			if (this->op == _NOT_OP_) return _BOOLEAN_;
			
			ValueType l_type = this->left_node->determine_final_type();
			
			for(Operator op : {_AND_OP_, _OR_OP_}){
				if (this->op == op){
					if (l_type == _STRING_ || r_type == _STRING_)
						throw InconsistentTypesError();
					return _BOOLEAN_;
				}
			}
			
			for(Operator op : {_EQUAL_OP_, _NOT_EQUAL_OP_}){
				if (this->op == op)
					return _BOOLEAN_;
			}
			
			for(Operator op : {_GT_OP_, _GTE_OP_, _LT_OP_, _LTE_OP_}){
				if (this->op == op){
					if (l_type == _STRING_ || l_type == _BOOLEAN_ || r_type == _STRING_ || r_type == _BOOLEAN_)
						throw InconsistentTypesError();
					return _BOOLEAN_;
				}
			}
			
			if (op == _PLUS_OP_){
				if (l_type == _STRING_ && r_type == _STRING_){
					return _STRING_;
				}
			}
			
			if (l_type == _INTEGER_ && r_type == _INTEGER_) return _INTEGER_;
			
			if ((l_type == _DECIMAL_ && (r_type == _DECIMAL_ || r_type == _INTEGER_)))
				return _DECIMAL_;
				
			if ((r_type == _DECIMAL_ && (l_type == _DECIMAL_ || l_type == _INTEGER_)))
				return _DECIMAL_;
			
				
			throw InconsistentTypesError();
			
			
		}
		
//		void check_semantic(){
//			
//		}
		
		
		void _repr_(){
//			std::cout << "{" << this->determine_final_type() <<"} [ ";
			std::cout << " [ ";
			
			if (this->left_node)
				this->left_node->_repr_();
			
			std::cout << " " << this->op << " ";
			
			this->right_node->_repr_();
			
			std::cout << " ] ";
		}
			
};

#include "../symbol_table/symbol_table.hpp"

class OperandNodeWithVariable : public ExpressionAST{
	Variable* variable;
	
	public:

		OperandNodeWithVariable(Variable* variable) : ExpressionAST(_OPERAND_NODE_){
			this->variable = variable;
		}
		
		ValueType determine_final_type(){
			return this->variable->get_data_type();
		}
		
		void _repr_(){
			std::cout << " [ ";
			std::cout << variable->get_symbol_name();
			std::cout << " ] ";
		}
		
	
	
};



std::map<ValueType, std::string> ValueType_to_default_value_mapping {
	{_VOID_, "N/A"},
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

		OperandNodeWithConstant(ValueType operand_type, std::string operand_value) : ExpressionAST(_OPERAND_NODE_){
			this->operand_type = operand_type;
			this->operand_value = operand_value;
		}
		
		OperandNodeWithConstant(ValueType operand_type) : ExpressionAST(_OPERAND_NODE_){
			this->operand_type = operand_type;
			this->operand_value = ValueType_to_default_value_mapping.find(operand_type)->second;
		}
		
		ValueType determine_final_type(){
			return this->operand_type;
		}
		
		void _repr_(){
			std::cout << operand_value;
		}
		
		// evaluate simply returns string value	
};



class OperandNodeWithFunctionCall : public ExpressionAST{
	Function* function_to_call;
	std::vector<ExpressionAST*> param_expressions;
	
	public:
		OperandNodeWithFunctionCall(Function* func_to_call, std::vector<ExpressionAST*> param_expressions) : ExpressionAST(_OPERAND_NODE_){
			this->function_to_call = func_to_call;
			this->param_expressions = param_expressions;
		}
		
		ValueType determine_final_type(){ // check_semantic()
			if(param_expressions.size() != function_to_call->get_parameters().size())
				throw std::exception();
				
			for(int i=0; i< param_expressions.size(); i++){
				ValueType param_expr_type = param_expressions.at(i)->determine_final_type();
				ValueType param_type = function_to_call->get_parameters().at(i)->get_data_type();
				
				if (param_expr_type != param_type)
					throw InconsistentTypesError();
			}
			
			return this->function_to_call->get_return_type();
			
		}
		
		void _repr_(){
			std::cout << " [ Function Call: " << this->function_to_call->get_symbol_name() << " : ( ";
			for(ExpressionAST* exp : param_expressions){
				exp->_repr_();
				std::cout << ", ";
			}
			
			std::cout << ") ]";
			
		}
};


#endif
