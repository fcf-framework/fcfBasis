#ifndef _FCF_BASIS__BITS__PART_EXCEPTION__ERROR_DECL_HPP___
#define _FCF_BASIS__BITS__PART_EXCEPTION__ERROR_DECL_HPP___

#include "../../macro.hpp"
#include "ExceptionPredecl.hpp"

namespace fcf {

  /**
   * @brief Lightweight error holder for exception-style reporting.
   *
   * The type can store a registered exception name and optionally update
   * an external Exception object. If loud is true, raise() also throws
   * the generated exception.
   */
  struct FCF_BASIS_DECL_EXPORT Error {
    /** @brief If true, raise() throws the generated exception. */
    bool        loud;

    /** @brief Registered exception name, or null when no error is set. */
    const char* error;

    /** @brief Optional external exception object used to store details. */
    Exception*  exception;

    /**
     * @brief Default constructor.
     *
     * Creates a silent error state with no registered error name.
     */
    inline Error();

    /**
     * @brief Constructs an error state with loud mode.
     *
     * @param a_loud If true, raise() throws generated exceptions.
     */
    inline Error(bool a_loud);

    /**
     * @brief Constructs a silent error state from an exception object.
     *
     * @param a_exception Exception whose registered name is used as error name.
     */
    inline Error(Exception*  a_exception);

    /**
     * @brief Constructs an error state from an exception object.
     *
     * @param a_loud If true, raise() throws generated exceptions.
     * @param a_exception Exception whose registered name is used as error name.
     */
    inline Error(bool a_loud, Exception*  a_exception);

    /**
     * @brief Checks whether an error is set.
     *
     * @return true if the error name is not null, false otherwise.
     */
    inline operator bool();

    /**
     * @brief Checks whether no error is set.
     *
     * @return true if the error name is null, false otherwise.
     */
    inline bool operator!();

    /**
     * @brief Clears the current error state.
     *
     * Resets the error name and, if available, assigns a default Exception
     * object to the external exception pointer.
     */
    inline void clear();

    /**
     * @brief Raises an exception type.
     *
     * Stores the registered exception name, updates the external exception
     * object when available, and throws the exception if loud is true.
     *
     * @tparam TException Exception type to raise.
     * @param a_argPack Arguments forwarded to the exception constructor.
     *
     * @throws TException Thrown only when loud is true.
     */
    template <typename TException, typename ...TArgPack>
    void raise(TArgPack&& ...a_argPack);
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_EXCEPTION__ERROR_DECL_HPP___
