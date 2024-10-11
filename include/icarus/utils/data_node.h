/**
 * (c) 2024 Houssem Guissouma.
 * Licensed under the MIT License.
 *
 * @file icarus/utils/data_node.h
 * @brief Definition of the class NodeData.
 */
#pragma once

#include <memory>
#include <string>
#include <sstream>

#undef emit  // Common macro used for example in Qt.
#include <ryml/ryml.hpp>
#include <ryml/ryml_std.hpp>
#define emit

namespace icarus {

/**
 * @brief Node in a YAML/JSON data structure.
 * 
 * This class is a wrapper around the Ryml library for YAML parsing and emitting.
 * @ingroup StructuredData
 */
class DataNode {
public:

    /**
     * @brief Format of a data node buffer.
     */
    enum class Format {
		kYaml,  ///< YAML format.
		kJson   ///< JSON format.
	};

    /**
     * @brief Type of the data node. 
     */
    enum class Type { 
        kMap,      ///< Map (key-value pairs) type.
        kSeq,      ///< Sequence type.
        kUndefined ///< Undefined type.
    };

    /**
     * @brief Iterator for traversing the children of a data node.
     */
    class NodeIterator {
    public:
        /**
         * @brief Constructs a node iterator with a given tree and node ID.
         * 
         * @param tree Tree structure of the data node.
         * @param node_id ID of the node within the tree.
         */
        NodeIterator(std::shared_ptr<ryml::Tree> tree, size_t node_id);

        /**
		 * @brief Increments the iterator to the next child.
		 * 
		 * @returns Reference to the incremented iterator.
		 */
        NodeIterator& operator++();

        /**
		 * @brief Returns the current child node.
		 * 
		 * @returns Current child node.
		 */
        DataNode operator*() const;

        /**
         * @brief Compares two iterators for inequality. 
         * 
         * @param other Iterator to compare with.
         * @returns True if the iterators are unequal, false otherwise.
		 */
        bool operator!=(const NodeIterator& other) const;

    private:
        std::shared_ptr<ryml::Tree> tree_;  ///< Tree structure of the data node.
        size_t node_id_;                    ///< ID of the node within the tree.
    };

    /**
	 * @brief Constructs an empty data node with a given type.
     * 
     * @param type [opt] Type of the data node.
	 */
    explicit DataNode(Type type = Type::kUndefined);

    /**
     * @brief Constructs a DataNode object by parsing a local YAML/JSON file.
     * 
     * @param file_path Path of the YAML/JSON file to read from.
     */
    explicit DataNode(const std::string& file_path);

    /**
	 * @brief Copy constructor.
	 * 
	 * @param other Data node object to copy from.
	 */
    DataNode(const DataNode& other);

    /**
     * @brief Move constructor.
     *
     * @param other DataNode object to move from.
     */
    DataNode(DataNode&& other) noexcept;

    /**
	 * @brief Parses the data node from a string buffer.
	 * 
	 * @param content String buffer to parse the data from.
	 */
    void parseFromStr(const std::string& content);

    /**
	 * @brief Parses the data node from a YAML/JSON file.
	 * 
	 * @param file_path Path of the file to parse the data from.
	 */
    void parseFromFile(const std::string& file_path);

    /**
     * @brief Returns the first child as an iterator.
     * 
     * @returns Iterator representing the first child.
     */
    NodeIterator begin() const;

    /**
     * @brief Returns the end iterator for the children of the data node.
	 * 
	 * @returns End iterator for the children of the data node.
	 */
    NodeIterator end() const;

    /**
     * @brief Sets the data node to a given value.
     * 
     * @param value Value to set the root node to.
     * @tparam T Type of the value to set, e.g., std::string, int, float.
     */
    template<typename T>
    DataNode& operator<<(const T& value) {
        tree_->ref(node_id_) << value;
        return *this;
    }

    /**
     * @brief Assigns an existing string to the data node.
     * 
     * @param value String to assign to the node.
     * @returns Reference to the data node.
     */
    DataNode& operator=(const char* value);

    /**
     * @brief [Assignment operator=] Returns a data node by copying the data from another node.
     * 
     * @param other Data node to copy from.
     */
    DataNode operator=(const DataNode& other);

    /**
     * @brief Retrieves a child node from the data node (map) using the operator [].
     *
     * @param key Key of the child node to retrieve.
     * @returns Retrieved child DataNode with the given key.
     * @throws std::runtime_error If the node is not a map.
     */
    DataNode operator[](const std::string& key) const;

    /**
     * @copydoc DataNode::operator[](const std::string& key) const.
     * 
     * If the key is not found, a new child node with the given key is created.
     */
    DataNode operator[](const std::string& key);

    /**
	 * @brief Retrieves a child node from the data node (sequence) using the operator [].
	 *
	 * @param index Index of the child node to retrieve.
	 * @returns Retrieved child DataNode at the given index.
	 * @throws std::runtime_error If the node is not a sequence.
	 */
    DataNode operator[](size_t index) const;

    DataNode operator[](size_t index);

    template<typename T>
    T as() const {
        T value{};
        tree_->cref(node_id_) >> value;
        return value;
	}

    std::string as_str() const {
        std::string value = "";
        tree_->cref(node_id_) >> value;

        if (value == "~" || value == "null") {
            return "";
        } else {
			return value;
		}
    }

    /**
     * @brief Returns whether the data node is valid.
     *
     * @returns True if the data node is valid, false otherwise (e.g., uninitialized).
     */
    bool isValid() const;

    /**
	 * @brief Returns whether the data spec is a map.
	 * 
	 * @returns True if the data spec is a map, false otherwise.
	 */
    bool isMap() const;

    /**
     * @brief Returns whether the data spec is a sequence. 
     * 
     * @returns True if the data spec is a sequence, false otherwise.
	 */
    bool isSeq() const;

    /**
	 * @brief Returns whether the data spec is a value.
	 * 
	 * @returns True if the data spec is a value, false otherwise.
     */
    bool isVal() const;

    /**
     * @brief Returns whether the data spec is a key-value pair.
     * 
     * @returns True if the data spec is a key-value pair, false otherwise.
	 */
    bool isKeyVal() const;

    /**
	 * @brief Returns the key of the data node, if it has one.
	 * 
	 * @returns Key of the data node as string.
	 */
    std::string getKey() const;

    /**
     * @brief Returns the first child of the data node, if it has one.
     * 
     * @returns First child of the data node.
     */
    DataNode first() const;

    /**
     * @brief Checks if the data node has a child with a given key.
     * 
     * @param key Key of the child to check for.
     */
    bool hasChild(const char* key) const;

    /**
	 * @brief Gets the number of children of the data node.
     * 
     * @returns Number of children of the data node.
	 */
    size_t getNumChildren() const;

    /**
	 * @brief Prints the data node to the console.
	 *  
	 * @param format [opt] Format to emit the data node in.
	 */
    void print(Format format = Format::kYaml) const;

    /**
     * @brief Writes the data spec to a YAML/JSON file.
     * 
     * @param output_file_path Path of the file to write the data spec to.
     * @param format [opt] Format to emit the data node in.
     * @throws std::runtime_error If the file cannot be opened for writing.
	 */
    void writeToFile(const std::string& output_file_path, Format format = Format::kYaml) const;

    /**
     * @brief Gets child map with a given key from the data node, if it is a sequence.
     *
     * @param key Key of the YAML node to be returned.
     * @returns Map YAML node with the given key.
     * @throws std::runtime_error If the node is not a sequence or key not within the sequence.
     */
    DataNode getMapFromSeq(const std::string& key) const;

    /**
     * @brief Returns the vector of strings corresponding to the data spec sequence.
     *
     * @returns Vector of strings from the data spec sequence.
     */
    std::vector<std::string> getSeqStrings();

private:
    /**
	 * @brief Constructs a data node with a given tree and node ID.
	 * 
	 * @param tree Tree structure of the data node.
     * @param node_id ID of the node within the tree.
	 */
    DataNode(std::shared_ptr<ryml::Tree> tree, size_t node_id);

    /**
     * @brief Emits the data node in YAML format.
     *
     * @returns YAML representation of the data node as a string.
     */
    std::string emitYaml() const;

    /**
     * @brief Emits the data node in JSON format.
     *
     * @returns JSON representation of the data node as a string.
     */
    std::string emitJson() const;

    /**
	 * @brief Converts a csubstr buffer to a string.
	 *
	 * @param buffer csubstr buffer to convert to a string.
	 * @returns Converted string.
	 */
    std::string toStr(const c4::csubstr& buffer) const;

    /// Tree structure of the data node.
    std::shared_ptr<ryml::Tree> tree_;
    /// ID of the data node within the tree.
    size_t node_id_;
};

} // namespace icarus
