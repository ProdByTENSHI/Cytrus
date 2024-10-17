#include "Cytrus.h"

#include <iostream>
#include <map>
#include <sstream>

#include <assert.h>

namespace tenshi {
// ##########################//
//    <== CYTRUS FILE ==>    //
// ##########################//
CytrusFile::CytrusFile(const std::string &filePath) : m_FilePath(filePath) {}

CytrusFile::~CytrusFile() {}

/* FILE FORMAT:
* Node:
        "Content",
        "Content2",
        "Content3",

        Child-Node:
                …
                …
                …
*/
void CytrusFile::SerializeNode(const Node &node) {
  static u32 indentationLevel = 0;

  OpenFile();
  Indent(indentationLevel);
  m_FileStream << node.m_Name << ":\n";

  indentationLevel += INDENTATION_PER_NODE_LEVEL;
  for (u32 i = 0; i < node.m_Content.size(); i++) {
    Indent(indentationLevel);

    auto &_value = node.m_Content[i];
    m_FileStream << '\u0022' << _value << '\u0022';
    if (node.m_ChildNodes.size() > 0 ||
        (i < node.m_Content.size() - 1 && node.m_Content.size() != 0)) {
      m_FileStream << ",";
    }

    m_FileStream << std::endl;
  }

  if (node.m_ChildNodes.size() <= 0) {
    indentationLevel = 0;
    m_FileStream.close();
  }

  for (auto &child : node.m_ChildNodes) {
    indentationLevel += INDENTATION_PER_NODE_LEVEL;
    SerializeNode(*child.second);
  }
}

std::vector<Token> CytrusFile::Tokenize(const std::string &input) {
  std::vector<Token> _tokens;

  if (!OpenFile())
    return _tokens;

  std::stringstream _buffer;
  _buffer << input;

  std::string _currentWord;
  bool _isWord = false;
  bool _isInvalid = false;

  for (u32 i = 0; i < _buffer.str().size(); i++) {
    char _char = _buffer.str()[i];
    Token _token;

    if (_char == ' ' || _char == '\n' || _char == '\t' || _char == '\r' ||
        _char == '\0') {
      if (!_currentWord.empty()) {
        _currentWord += ' ';
        continue;
      } else {
        continue;
      }
    }

    switch (_char) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
      _isWord = true;
      _currentWord += _char;
      break;

    case ':':
      _isWord = false;
      _token.m_Type = TokenType::ChildList;
      _token.m_Content = ':';
      break;

    case '"':
      _isWord = false;
      _token.m_Type = TokenType::QMarks;
      _token.m_Content = '"';
      break;

    case ',':
      _isWord = false;
      _token.m_Type = TokenType::Comma;
      _token.m_Content = ',';
      break;

    default:
      _isInvalid = true;
      _isWord = false;
      LOG("Token is not valid " << _token.m_Content);
      break;
    }

    if (_isInvalid || _token.m_Content.empty()) {
      _isInvalid = false;
      continue;
    }

    if (!_isWord && _currentWord.size() > 0) {
      Token _strToken;
      _strToken.m_Type = TokenType::Word;
      _strToken.m_Content = _currentWord;

      _tokens.push_back(_strToken);

      if (!_token.m_Content.empty()) {
        _tokens.push_back(_token);
      }

      _currentWord.clear();
      _isInvalid = false;

      continue;
    }

    _tokens.push_back(_token);
    _isInvalid = false;
  }

  return _tokens;
}

std::vector<Node *> CytrusFile::Parse(const std::vector<Token> &tokens) {
  // Struct to group up Data needed for each Node to keep Track of the
  // Relationships
  struct NodeParseData {
    Node *m_Node = nullptr;
    i32 m_ParentIndex = -1;
    i32 m_Index = -1;

    // If the last scanned Token Group implicated that another Value or Node is
    // following
    bool m_ChildrenFollowing = false;
  };

  std::vector<Node *> _data;

  if (tokens.size() <= 1) {
    LOG("Cannot parse Tokens because there are only "
        << tokens.size() << " Tokens in the given Vector");
    return _data;
  }

  NodeParseData _currentNode;
  u32 _currentNodeIndex = 0;
  std::vector<NodeParseData> _nodeParseDataVec;
  NodeParseData _parseData;
  for (i32 i = 0; i < tokens.size(); i++) {
    bool _wasCorrect = false;

    // <== CHECK AGAINST GRAMMAR ==>
    // Create new Node
    if (tokens.size() >= i + 1 &&
        (tokens[i].m_Type == TokenType::Word &&
         tokens[i + 1].m_Type == TokenType::ChildList)) {
      Node *node = new Node(tokens[i].m_Content);
      if (_nodeParseDataVec.size() == 0) {
        _parseData.m_Node = node;
        _currentNode.m_Node = node;
        _nodeParseDataVec.push_back(_parseData);
        _data.push_back(node);

        LOG("Created first Root Node " << node->m_Name);

        i += 2;
        continue;
      }

      // Check if Node is a Child or not
      if (_currentNode.m_ChildrenFollowing) {
        LOG("Created Child Node of " << _currentNode.m_Node->m_Name << ": "
                                     << node->m_Name);
        _currentNode.m_Node->AddChild(*node);
        _parseData.m_ParentIndex = _currentNode.m_Index;
      } else {
        LOG("Created Root Node " << node->m_Name);
        _data.push_back(node);
      }

      _parseData.m_Node = node;
      _currentNode.m_Node = node;
      _nodeParseDataVec.push_back(_parseData);

      // Skip the Parsed Tokens
      i += 2;
    }

    // Create Value
    if (tokens.size() >= i + 2 && (tokens[i].m_Type == TokenType::QMarks &&
                                   tokens[i + 1].m_Type == TokenType::Word &&
                                   tokens[i + 2].m_Type == TokenType::QMarks)) {
      if (_currentNode.m_Node == nullptr) {
        std::cerr << "[Cytrus] Error parsing File " << m_FilePath << ": "
                  << " Values have to be Children of Nodes" << std::endl;
        i += 3;
        continue;
      }

      _currentNode.m_Node->SetString(tokens[i + 1].m_Content);
      LOG("Created Value: " << _currentNode.m_Node->GetString(
              _currentNode.m_Node->m_Content.size() - 1));

      if (tokens.size() >= i + 3 && tokens[i + 3].m_Type == TokenType::Comma) {
        _currentNode.m_ChildrenFollowing = true;
        i += 4;
        continue;
      } else {
        LOG("Tobanga Nö, Tobanga Nö");
        _currentNode.m_ChildrenFollowing = false;
        i += 3;
        continue;
      }
    }
    // <===========================>
  }

  return _data;
}

std::vector<Node *> CytrusFile::DeserializeFile() {
  // Only holds Root Nodes
  // The Children are hold by the Root Nodes itself
  std::vector<Node *> _data;

  if (!OpenFile()) {
    return _data;
  }

  std::stringstream _stream;
  _stream << m_FileStream.rdbuf();
  std::vector<Token> _tokens = Tokenize(_stream.str());

  _data = Parse(_tokens);
  LOG("Finished Deserialization and created " << _data.size()
                                              << " Root Level Nodes");
  return _data;
}

bool CytrusFile::OpenFile() {
  if (m_FileStream.is_open()) {
    return true;
  }

  m_FileStream.open(m_FilePath, std::ios::in | std::ios::out | std::ios::app);
  if (!m_FileStream.is_open()) {
    LOG("ERROR: Could not Open File " << m_FilePath);
    return false;
  }

  return true;
}

void CytrusFile::CloseFile() { m_FileStream.close(); }

void CytrusFile::Indent(u32 indentationLevel) {
  for (u32 i = 0; i < indentationLevel; i++) {
    m_FileStream << " ";
  }

  m_FileStream.flush();
}

} // namespace tenshi
