// --> Arnoldo Solis
// The 2D points class is meant to to hold a sequence of points of arbitrary size.
// It can be potentially used for a graph.

#ifndef CSCI335_HOMEWORK2_POINTS2D_H_
#define CSCI335_HOMEWORK2_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project
{
  // Sample Usage: Graph
  template <typename Object>
  class Points2D
  {
  public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation for it.

    // Zero-parameter constructor.
    // Set size to 0.
    Points2D()
    {
      size_ = 0;
      sequence_ = nullptr;
    }

    // Copy-constructor.
    Points2D(const Points2D &rhs)
    {
      // Sets the size of the new sequence
      size_ = rhs.size_;
      // Initializes new sequence dynamically
      sequence_ = new std::array<Object, 2>[size_];
      // loops through sequence to copying data
      for (size_t i = 0; i < size_; i++)
      {
        sequence_[i] = rhs.sequence_[i];
      }
    }
    // Copy-assignment. If you have already written
    // the copy-constructor and the move-constructor
    // you can just use:
    // {
    // Points2D copy = rhs;
    // std::swap(*this, copy);
    // return *this;
    // }
    Points2D &operator=(const Points2D &rhs)
    {
      Points2D copy = rhs;
      std::swap(*this, copy);
      return *this;
    }

    // Move-constructor.
    Points2D(Points2D &&rhs) : sequence_{rhs.sequence_}, size_{rhs.size_}
    {
      rhs.sequence_ = nullptr;
      rhs.size_ = 0;
    }

    // Move-assignment.
    // Just use std::swap() for all variables.
    Points2D &operator=(Points2D &&rhs)
    {
      // Takes data of sequence_ from callee and assigns it to caller
      std::swap(this->sequence_, rhs.sequence_);
      // Takes data of size_ from callee and assigns it to caller
      std::swap(this->size_, rhs.size_);
      return *this;
    }

    ~Points2D()
    {
      delete sequence_;
      sequence_ = nullptr;
    }

    // End of big-five.

    // One parameter constructor.
    Points2D(const std::array<Object, 2> &item)
    {
      // Divides size by 2 because each sequence has 2 objects in them.
      size_ = item.size() / 2; // 2 points
      sequence_ = new std::array<Object, 2>(item); // Initializes a new sequence dynamically
    }

    // Read a chain from standard input.
    void ReadPoints2D()
    {
      // Part of code included (without error checking).
      std::string input_line;
      std::getline(std::cin, input_line);
      std::stringstream input_stream(input_line);
      if (input_line.empty()) return;
      // Read size of sequence (an integer).
      int size_of_sequence;
      input_stream >> size_of_sequence;
      // Add code here.
      size_ = size_of_sequence;
      sequence_ = new std::array<Object, 2>[size_of_sequence];
      Object token;
      for (int i = 0; input_stream >> token; ++i)
      {
        // Read coordinates.
        // Fill sequence_ here.
        sequence_[i][0] = token;
        input_stream >> token;
        sequence_[i][1] = token;
      }
    }

    size_t size() const
    {
      return size_;
    }

    // @location: an index to a location in the given sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2> &operator[](size_t location) const
    {
      if (location > size_)
      {
        abort();
      }
      return sequence_[location];
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    friend Points2D operator+(const Points2D &c1, const Points2D &c2)
    {
      // Initializes new sequence
      Points2D<double> c3;
      // If the first sequence is greater then the second sequence
      if (c1.size() > c2.size())
      {
        c3 = c1;
        // Add all the points from the second sequence to the first sequence
        for (size_t i = 0; i < c3.size(); i++)
        {
          c3.sequence_[i][0] += c2.sequence_[i][0];
          c3.sequence_[i][1] += c2.sequence_[i][1];
        }
        return c3;
      }
      // If the second sequence is greater then the first sequence
      else if (c1.size() < c2.size())
      {
        c3 = c2;
        // Add all the points from the first sequence to the second sequence
        for (size_t i = 0; i < c3.size(); i++)
        {
          c3.sequence_[i][0] += c1.sequence_[i][0];
          c3.sequence_[i][1] += c1.sequence_[i][1];
        }
        return c3;
      }
      else // If both sequences are of same size
      {
        c3 = c1;
        // Both sequences are evenly added, you could use either sequence as a return value
        for (size_t i = 0; i < c3.size(); i++)
        {
          c3.sequence_[i][0] += c2.sequence_[i][0];
          c3.sequence_[i][1] += c2.sequence_[i][1];
        }
        return c3;
      }
    }

    // Overloading the << operator.
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2d)
    {
      // If sequence does not exists
      if (some_points2d.sequence_ == nullptr)
      {
        out << "()"; // print empty sequence
      }
      // If a sequence with a size of one exists
      if (some_points2d.sequence_ != nullptr && some_points2d.size() == 1)
      {
        out << "(" << some_points2d.sequence_->at(0) << ", " << some_points2d.sequence_->at(1) << ")"; // print sequence with a size of 1
      }
      // If a sequence with a size greater than 1
      if (some_points2d.sequence_ != nullptr && some_points2d.size() > 1)
      {
        for (size_t i = 0; i < some_points2d.size(); i++)
        {
          out << "(" << some_points2d.sequence_[i].at(0) << ", " << some_points2d.sequence_[i].at(1) << ")"; // Print sequence with size greater than 1
        }
      }
      out << std::endl;
      return out;
    }

  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;
    // Size of the sequence.
    size_t size_;
  };

} // namespace teaching_project
#endif // CSCI_335_HOMEWORK2_POINTS2D_H_
