#include "block.hpp"

#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <utility>

using EVP_MD_CTX_ptr = std::unique_ptr<EVP_MD_CTX, EVP_MD_CTX_Deleter>;

Block::Block(const std::unordered_map<std::string, std::string>& dictionary)
    : index_(0), timestamp_(getCurrentTimestamp()), nonce_(0) {
  for (const auto& [key, value] : dictionary) {
    if (key == "index") {
      index_ = std::stoll(value);
    } else if (key == "timestamp") {
      timestamp_ = value;
    } else if (key == "data") {
      data_ = value;
    } else if (key == "prev_hash") {
      prev_hash_ = value;
    } else if (key == "nonce") {
      nonce_ = std::stoll(value);
    } else if (key == "hash") {
      hash_ = value;
    }
  }

  if (hash_.empty()) {
    hash_ = createSelfHash();
  }
}

Block::Block(const int64_t index, const std::string& data,
             std::string prev_hash)
    : index_(index), data_(data), prev_hash_(std::move(prev_hash)), dat_(data) {
  timestamp_ = getCurrentTimestamp();
  nonce_ = 0;
  hash_ = createSelfHash();
}

std::unordered_map<std::string, std::string> Block::toDict() const {
  std::unordered_map<std::string, std::string> info;
  info["index"] = std::to_string(index_);
  info["timestamp"] = timestamp_;
  info["prev_hash"] = prev_hash_;
  info["hash"] = hash_;
  info["data"] = data_;
  info["nonce"] = std::to_string(nonce_);
  return info;
}

int64_t Block::getIndex() const { return index_; }

const std::string& Block::getTimestamp() const { return timestamp_; };

const std::string& Block::getData() const { return data_; };

const std::string& Block::getPrevHash() const { return prev_hash_; };

const std::string& Block::getHash() const { return hash_; };

int64_t Block::getNonce() const { return nonce_; };

std::string Block::createSelfHash() const {
  std::stringstream ss;
  ss << index_ << timestamp_ << data_ << prev_hash_ << nonce_;
  std::string data_to_hash = ss.str();

  EVP_MD_CTX* context = EVP_MD_CTX_new();
  if (!context) {
    return "";
  }

  unsigned char hash[EVP_MAX_MD_SIZE];
  unsigned int hash_length = 0;
  std::string result;

  do {
    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) break;
    if (EVP_DigestUpdate(context, data_to_hash.c_str(), data_to_hash.size()) !=
        1)
      break;
    if (EVP_DigestFinal_ex(context, hash, &hash_length) != 1) break;

    std::stringstream hash_ss;
    for (unsigned int i = 0; i < hash_length; i++) {
      hash_ss << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(hash[i]);
    }
    result = hash_ss.str();
  } while (false);

  EVP_MD_CTX_free(context);
  return result;
}

std::string Block::getCurrentTimestamp() {
  const std::time_t now = std::time(nullptr);
  const std::tm* tm_ptr = std::localtime(&now);

  std::stringstream ss;
  ss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S");
  return ss.str();
}

Block create_first_block() {
  std::unordered_map<std::string, std::string> block_data_;
  block_data_["index"] = "0";
  block_data_["data"] = "First block data";
  block_data_["prev_hash"] = "";

  return Block(block_data_);
}
