#include "Cytrus.h"

#include <iostream>
#include <sstream>

namespace tenshi {
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
    // if (node.m_ChildNodes.size() > 0 ||
    //     (i < node.m_Content.size() - 1 && node.m_Content.size() != 0)) {
    //   m_FileStream << ",";
    // }

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

      // case ',':
      //   _isWord = false;
      //   _token.m_Type = TokenType::Comma;
      //   _token.m_Content = ',';
      //   break;

    default:
      _isInvalid = true;
      _isWord = false;
      std::cerr << "[Cytrus] No Token matches the Char " << _char << std::endl;
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

      if (!_token.m_Content.empty())
        _tokens.push_back(_token);

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
  std::vector<Node *> _data;

  if (tokens.size() <= 1) {
    std::cout
        << "[Cytrus] Cannot parse Tokens because it is only 1 or less Tokens"
        << std::endl;
  }

  Node *currentNode = nullptr;
  std::vector<Token> _parseGroup;
  for (i32 i = 0; i < tokens.size(); i++) {
    _parseGroup.push_back(tokens[i]);
    if (_parseGroup.size() == 1)
      continue;

    // Check against Grammar
    bool _wasCorrect = false;
    if (_parseGroup.size() == 2) {
      // Create New Node
      if (_parseGroup[0].m_Type == TokenType::Word &&
          _parseGroup[1].m_Type == TokenType::ChildList) {
        Node *newNode = new Node(_parseGroup[0].m_Content);
        if (currentNode != nullptr) {
          // Set Node as child of parent Node
          currentNode->AddChild(_parseGroup[0].m_Content);
        }

        currentNode = newNode;
        _data.push_back(currentNode);
        _wasCorrect = true;
      }
    } else if (_parseGroup.size() == 3) {
      if (_parseGroup[0].m_Type == TokenType::QMarks &&
          _parseGroup[1].m_Type == TokenType::Word &&
          _parseGroup[2].m_Type == TokenType::QMarks) {
        // Create Value for current Node
        currentNode->SetString(_parseGroup[1].m_Content);

        _wasCorrect = true;
      }
    }

    if (!_wasCorrect)
      continue;

    _parseGroup.clear();
  }

  return _data;
}

std::vector<Node *> CytrusFile::DeserializeFile() {
  std::vector<Node *> _data;

  if (!OpenFile()) {
    std::cerr << "[Cytrus] Could not open " << m_FilePath << std::endl;
    return _data;
  }

  std::stringstream _stream;
  _stream << m_FileStream.rdbuf();
  std::vector<Token> _tokens = Tokenize(_stream.str());

  _data = Parse(_tokens);

  return _data;
}

bool CytrusFile::OpenFile() {
  if (m_FileStream.is_open()) {
    return true;
  }

  m_FileStream.open(m_FilePath, std::ios::in | std::ios::out | std::ios::app);
  if (!m_FileStream.is_open()) {
    std::cout << "[Cytrus] Error: Could not open File " << m_FilePath
              << std::endl;
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
