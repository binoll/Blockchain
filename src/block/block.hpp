#pragma once

#include <openssl/evp.h>

#include <sstream>
#include <string>
#include <unordered_map>

struct EVP_MD_CTX_Deleter {
  void operator()(EVP_MD_CTX* ctx) const { EVP_MD_CTX_free(ctx); }
};

class Block {
 public:
  explicit Block(
      const std::unordered_map<std::string, std::string>& dictionary);

  Block(int64_t index, const std::string& data, std::string prev_hash = "");

  [[nodiscard]] std::unordered_map<std::string, std::string> toDict() const;

  [[nodiscard]] int64_t getIndex() const;

  [[nodiscard]] const std::string& getTimestamp() const;

  [[nodiscard]] const std::string& getData() const;

  [[nodiscard]] const std::string& getPrevHash() const;

  [[nodiscard]] const std::string& getHash() const;

  [[nodiscard]] int64_t getNonce() const;

 private:
  [[nodiscard]] std::string createSelfHash() const;

  [[nodiscard]] static std::string getCurrentTimestamp();

  int64_t index_;
  std::string timestamp_;
  std::string data_;
  std::string prev_hash_;
  std::string hash_;
  int64_t nonce_;
  std::string dat_;
};

extern Block create_first_block();
