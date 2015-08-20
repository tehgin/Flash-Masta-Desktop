/*! \file
 *  \brief File containing the declaration of the \ref ngp_cartridge class.
 *  
 *  File containing the header information and declaration of the
 *  \ref ngp_cartridge class. This file includes the minimal number of files
 *  necessary to use any instance of the \ref ngp_cartridge class.
 */

#ifndef __NGP_CARTRIDGE_H__
#define __NGP_CARTRIDGE_H__

#include "cartridge.h"

class linkmasta_device;
class ngp_chip;

/*! \brief ngp_cartridge
 *  
 *  Class representing a Neo Geo Pocket game cartridge. Stores information
 *  relevant to cartridge storage and hardware information, such as the number
 *  of onboard chips and exactly how the chips are divided into blocks.
 *  Implements functions for performing high-level operations on a cartridge.
 *  
 *  This class does not support copying or the copy assignment operator (=).
 *  
 *  This class is *not* thread-safe. use caution when working in a multithreaded
 *  environment.
 */
class ngp_cartridge: public cartridge
{
private:
  static const unsigned int MAX_NUM_CHIPS = 2;

public:
  
  /*! \brief Class constructor.
   *  
   *  Main constructor for the class. Iniitalizes members with default values
   *  and supplied parameters.
   *  
   *  \param linkmasta Pointer to a valid instance of \ref linkmasta_device to
   *         use to communicate with the cartridge hardware. Note that the new
   *         \ref ngp_cartridge instance does **not** delete the
   *         \ref linkmasta_device upon destruction and thus the responsibility
   *         of preventing memory leaks falls to this function's caller.
   */
                        ngp_cartridge(linkmasta_device* linkmasta);
  
  /*! \brief Class destructor.
   *  
   *  Destructor for the class. Cleans up and frees resources. Closes all open
   *  communication channels.
   *  
   *  **Note:** Does not deallocate the \dev linkmasta_device instance assigned
   *  at construction. It is the responsibility of an external controller to
   *  free that object.
   */
                        ~ngp_cartridge();
  
  /*!
   *  \see cartridge::system()
   *  
   *  \returns \ref system_type::NEO_GEO_POCKET - The cartridge is compatible
   *           with a Neo Geo Pocket or Neo Geo Pocket Color system.
   */
  system_type           system() const;
  
  /*!
   *  \see cartridge::descriptor()
   */
  const cartridge_descriptor* descriptor() const;
  
  
  
  /*!
   *  \see cartridge::init()
   */
  void                  init();
  
  /*!
   *  \see cartridge::backup_cartridge_game_data(std::ostream& fout, task_controller* controller = nullptr)
   */
  void                  backup_cartridge_game_data(std::ostream& fout, task_controller* controller = nullptr);
  
  /*!
   *  \see cartridge::restore_cartridge_game_data(std::istream& fin, task_controller* controller = nullptr)
   */
  void                  restore_cartridge_game_data(std::istream& fin, task_controller* controller = nullptr);
  
  /*!
   *  \see cartridge::compare_cartridge_game_data(std::istream& fin, task_controller* controller = nullptr)
   */
  bool                  compare_cartridge_game_data(std::istream& fin, task_controller* controller = nullptr);
  
  /*!
   *  \see cartridge::backup_cartridge_save_data(std::ostream& fout, task_controller* controller = nullptr)
   */
  void                  backup_cartridge_save_data(std::ostream& fout, task_controller* controller = nullptr);
  
  /*!
   *  \see cartridge::restore_cartridge_save_data(std::istream& fin, task_controller* controller = nullptr)
   */
  void                  restore_cartridge_save_data(std::istream& fin, task_controller* controller = nullptr);
  
  /*!
   *  \see cartridge::compare_cartridge_save_data(std::istream& fin, task_controller* controller = nullptr)
   */
  bool                  compare_cartridge_save_data(std::istream& fin, task_controller* controller = nullptr);
  
  
  
  /*! \brief Tests the provided \ref linkmasta_device for whether or not a
   *         valid cartridge is present.
   *
   *  Tests the provided \ref linkmasta_device hardware for whether or not a
   *  valid cartridge is present. This can be used to determine whether or not
   *  to create a new instance of this class.
   *  
   *  This function is a blocking function that can take several seconds to
   *  complete. The function is provided as-is and any timeouts should be
   *  configured with the supplied \ref linkmasta_device beforehand. Does not
   *  initialize the supplied \ref linkmasta_device, and thus it is the
   *  responsibility of the caller to ensure that the device has been
   *  initialized by calling \ref linkmasta_device::init().
   *  
   *  \param linkmasta The \ref linkmasta_device to use to test if a cartridge
   *         is present.
   *
   *  \returns **true** A cartridge is present and accessible through the
   *           supplied \ref linkmasta_device instance.
   *  \returns **false** A cartridge is likely not present.
   */
  static bool           test_for_cartridge(linkmasta_device* linkmasta);
  
  
  
protected:
  
  /*! \brief Constructs a \ref cartridge_descriptor struct using information
   *         gathered from the associated \ref linkmasta_device.
   *  
   *  Uses the associated \ref linkmasta_device to query for information on the
   *  cartridge and its onboard chips. Gathers information on cartridge size and
   *  the number of flash storage chips on the cartridge. This function calls
   *  \ref build_chip_descriptor(unsigned int chip_i) automatically to gather
   *  information about the onboard hardware.
   *  
   *  Before building the descriptor, this function replaces the internally
   *  cached descriptor with the newly created one. To access the newly created
   *  descriptor, use \ref descriptor().
   *  
   *  This function is a blocking function that can take several seconds to
   *  complete. The function is provided as-is and any timeouts should be
   *  configured with the supplied \ref linkmasta_device beforehand.
   *  
   *  \see build_chip_descriptor(unsigned int chip_i)
   *  \see build_block_descriptor(unsigned int chip_i, unsigned int block_i)
   */
  void                  build_cartridge_destriptor();
  
  /*! \brief Creates and populates a \ref cartridge_descriptor::chip_descriptor
   *         struct using information gathered from the associated
   *         \ref linkmasta_device.
   *  
   *  Uses the associated \ref linkmasta_device to query for information on the
   *  cartridge's onboard flash storage chips. Gathers information on the chip's
   *  device id, manufacturer id, storge capacity, and sector layout. Calls
   *  \ref build_block_descriptor(unsigned int chip_i, unsigned int block_i)
   *  automatically to gather information about each sector. This function is
   *  automatically called by \ref build_cartridge_descriptor().
   *
   *  After building the descriptor, this function updates the internally
   *  cached descriptor with the newly created one. To access the result of this
   *  function, use \ref descriptor() to access the cartridge's descriptor, then
   *  access the structure at the desired index of
   *  \ref cartridge_descriptor::chips.
   *  
   *  This function is a blocking function that can take several seconds to
   *  complete. The function is provided as-is and any timeouts should be
   *  configured with the supplied \ref linkmasta_device beforehand.
   *  
   *  \param [in] chip_i The index of the chip to build the struct from. Index
   *         0 will refer to the first chip on the cartridge.
   *  
   *  \see build_cartridge_descriptor()
   *  \see build_block_descriptor(unsigned int chip_i, unsigned int block_i)
   */
  void                  build_chip_descriptor(unsigned int chip_i);
  
  /*! \brief Creats and populates a \ref cartridge_descriptor::block_descriptor
   *         struct using information gathered from the associated \ref linkmasta_device.
   *  
   *  Uses the associated \ref linkmasta_device to query for information on the
   *  specified chip's sectors. Gathers information on the sector's storage
   *  capacity, base address, and write protection status. This function is
   *  automatically called by \ref build_chip_descriptor(unsigned int chip_i).
   *  
   *  After building the descriptor, this function updates the internally
   *  cached descriptor with the newly created one. To access the result of this
   *  function, use \ref descriptor() to access the cartridge's descriptor, then
   *  access the structure at the desired index of
   *  \ref cartridge_descriptor::chips, and form there access the structure
   *  at the desired index of
   *  \ref cartridge_descriptor::chip_descriptor::blocks.
   *  
   *  This function is a blocking function that can take several seconds to
   *  complete. The function is provided as-is and any timeouts should be
   *  configured with the supplied \ref linkmasta_device beforehand.
   *  
   *  \param [in] chip_i The index of the chip to build the struct from. Index
             0 will refer to the first chip on the cartridge.
   *  \param [in] block_i The index of the block on the chip to build the
   *         descriptor from. Index 0 will refer to the first sector on the
   *         chip.
   *  
   *  \see build_cartridge_descriptor()
   *  \see build_chip_descriptor(unsigned int chip_i)
   */
  void                  build_block_descriptor(unsigned int chip_i, unsigned int block_i);
  
  
  
private:
  
  /*! \brief Disabled copy constructor.
   *  
   *  The copy constructor for this class. Because this class cannot be copied
   *  due to its nature, this method has been disabled. Instead, use one of the
   *  main constructors.
   *
   *  \param [in] other The original instance of the class to copy.
   *  
   *  \see ngp_cartridge(linkmasta_device* linkmasta)
   */
                        ngp_cartridge(const ngp_cartridge& other) = delete;
  
  /*! \brief Disabled copy assignment constructor.
   *  
   *  The copy assignment operator for this class. Because this class cannot be
   *  copied due to its nature, this method has been disabled.
   *  
   *  \param [in] other The original instance of the class to copy.
   *  
   *  \returns The instance of the class on which this method was called. I.e.,
   *           the left-hand side of the assignment operator.
   */
  ngp_cartridge&        operator=(const ngp_cartridge& other) = delete;
  
  
  
  /*! \brief Flag indicating that \ref init() has been previously called on this
   *         instance.
   *  
   *  Flag indicating that \ref init() has been previously called on this
   *  instance. This variable is set to **false** when the object is first
   *  constructed, then set to **true** once \ref init() has been called. This
   *  variable should not be set to **false** after it has previously been set
   *  to **true**.
   *  
   *  \see init()
   */
  bool                  m_was_init;
  
  /*! \brief Pointer to the \ref linkmasta_device that the object will use for
   *         communication with the hardware.
   *  
   *  Pointer to the \ref linkmasta_device that the object will use for
   *  communication with the hardware. This variable must be initialized with
   *  a valid pointer during object creation.
   *  
   *  \see linkmasta_device
   *  \see ngp_cartridge(linkmasta_device* linkmasta)
   */
  linkmasta_device*     m_linkmasta;
  
  /*! \brief A pointer to the cached \ref cartridge_descriptor struct that
   *         describes the hardware of the cartridge.
   *  
   *  A pointer to the cached \ref cartridge_descriptor struct that describes
   *  the hardware of the cartridge. This variable is set to **nullptr** until
   *  \ref init() or \ref build_cartridge_descriptor() is called.
   *  
   *  \see cartridge_descriptor
   *  \see init()
   *  \see build_cartridge_descriptor()
   */
  cartridge_descriptor* m_descriptor;
  
  /*! \brief The number of flash storage chips onboard the cartridge.
   *  
   *  The number of flash storage chips onboard the cartridge. Used to determine
   *  the length of the \ref m_chips array. This number is not initialized until
   *  \ref init() or \ref build_cartridge_descriptor() is called.
   *  
   *  \see m_chips
   *  \see init()
   *  \see build_cartridge_descriptor()
   */
  unsigned int          m_num_chips;
  
  /*! \brief An array of \ref ngp_chip pointers used for communication with the
   *         cartridge hardware.
   *
   *  Array of \ref ngp_chip pointers. The objects referenced in this array are
   *  used for communication with the cartridge's flash storage chips.
   *  Although the array is of size \ref MAX_NUM_CHIPS, not all values will be
   *  valid. Refer to \ref m_num_chips to determine the number of valid pointers
   *  in the array.
   *
   *  The elements in this array are only valid if \ref init() or
   *  \ref build_cartridge_descriptor() has been called previously.
   *
   *  \see ngp_chip
   *  \see MAX_NUM_CHIPS
   *  \see m_num_chips
  */
  ngp_chip*             m_chips[MAX_NUM_CHIPS];
};

#endif // __NGP_CARTRIDGE_H__
