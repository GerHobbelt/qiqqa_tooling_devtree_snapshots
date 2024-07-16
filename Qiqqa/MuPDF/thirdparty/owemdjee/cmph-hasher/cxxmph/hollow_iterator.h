#ifndef __CXXMPH_HOLLOW_ITERATOR_H__
#define __CXXMPH_HOLLOW_ITERATOR_H__

#include <vector>

namespace cxxmph {

using std::vector;

template <typename container_type>
struct is_empty {
 public:
  is_empty() : c_(NULL), p_(NULL) {};
  is_empty(const container_type* c, const vector<bool>* p) : c_(c), p_(p) {};
  bool operator()(typename container_type::const_iterator it) const {
    if (it == c_->end()) return false;
    return !(*p_)[it - c_->begin()];
  }
 private:
  const container_type* c_;
  const vector<bool>* p_;
};

template <typename iterator, typename is_empty>
struct hollow_iterator_base
	// fix warning C4996: 'std::iterator<std::forward_iterator_tag,int,ptrdiff_t,int *,int &>': warning STL4015: The std::iterator class template (used as a base class to provide typedefs) is deprecated in C++17. (The <iterator> header is NOT deprecated.) The C++ Standard has never required user-defined iterators to derive from std::iterator. To fix this warning, stop deriving from std::iterator and start providing publicly accessible typedefs named iterator_category, value_type, difference_type, pointer, and reference. Note that value_type is required to be non-const, even for constant iterators. You can define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING or _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS to suppress this warning.
    /* : public std::iterator<std::forward_iterator_tag,
                           typename iterator::value_type> */ {
 public:
  typedef hollow_iterator_base<iterator, is_empty> self_type;
  typedef self_type& self_reference;
  typedef typename iterator::reference reference;
  typedef typename iterator::pointer pointer;
  typedef typename iterator::value_type value_type;
  typedef typename iterator::difference_type difference_type;
  typedef typename iterator::iterator_category iterator_category;
  inline hollow_iterator_base() : it_(), empty_() { }
  inline hollow_iterator_base(iterator it, is_empty empty, bool solid) : it_(it), empty_(empty) {
    if (!solid) advance();
  }
  // Same as above, assumes solid==true.
  inline hollow_iterator_base(iterator it, is_empty empty) : it_(it), empty_(empty) {}
  inline hollow_iterator_base(const self_type& rhs) { it_ = rhs.it_; empty_ = rhs.empty_; }
  template <typename const_iterator>
  hollow_iterator_base(const hollow_iterator_base<const_iterator, is_empty>& rhs) { it_ = rhs.it_; empty_ = rhs.empty_; }

  reference operator*() { return *it_;  }
  pointer operator->() { return &(*it_); }
  self_reference operator++() { ++it_; advance(); return *this; }
  // self_type operator++() { auto tmp(*this); ++tmp; return tmp; }

  template <typename const_iterator>
  bool operator==(const hollow_iterator_base<const_iterator, is_empty>& rhs) { return rhs.it_ == it_; }
  template <typename const_iterator>
  bool operator!=(const hollow_iterator_base<const_iterator, is_empty>& rhs) { return rhs.it_ != it_; }

  // should be friend
  iterator it_;
  is_empty empty_;

 private:
  void advance() {
    while (empty_(it_)) ++it_;
  }
};

template <typename container_type, typename iterator>
inline auto make_solid(
   container_type* v, const vector<bool>* p, iterator it) ->
       hollow_iterator_base<iterator, is_empty<const container_type>> {
  return hollow_iterator_base<iterator, is_empty<const container_type>>(
      it, is_empty<const container_type>(v, p));
}

template <typename container_type, typename iterator>
inline auto make_hollow(
   container_type* v, const vector<bool>* p, iterator it) ->
       hollow_iterator_base<iterator, is_empty<const container_type>> {
  return hollow_iterator_base<iterator, is_empty<const container_type>>(
      it, is_empty<const container_type>(v, p), false);
}

template <typename iterator>
struct iterator_second : public iterator {
  iterator_second() : iterator() { }
  iterator_second(iterator it) : iterator(it) { }
  typename iterator::value_type::second_type& operator*() {
    return this->iterator::operator*().second;
  }
  const typename iterator::value_type::second_type& operator*() const {
    return this->iterator::operator*().second;
  }
  typename iterator::value_type::second_type* operator->() { return const_cast<typename iterator::value_type::second_type*>(&(this->iterator::operator->()->second)); }
  const typename iterator::value_type::second_type* operator->() const { return &(this->iterator::operator->()->second); }
};

template <typename iterator>
iterator_second<iterator> make_iterator_second(iterator it) {
  return iterator_second<iterator>(it);
}

}  // namespace cxxmph

#endif  // __CXXMPH_HOLLOW_ITERATOR_H__
