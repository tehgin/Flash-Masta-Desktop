#ifndef CARTRIDGETASK_H
#define CARTRIDGETASK_H

#include <QObject>
#include <mutex>
#include "tasks/task_controller.h"
#include "usb/usbfwd.h"

class cartridge;
class QProgressDialog;
class linkmasta_device;
struct libusb_context;
struct libusb_device;
struct libusb_device_handle;

class CartridgeTask : public QObject, public task_controller
{
  Q_OBJECT
public:
  explicit              CartridgeTask(QWidget *parent = 0);
  virtual               ~CartridgeTask();
  
  virtual void          go();
  
  virtual void          on_task_start(int work_expected);
  virtual void          on_task_update(task_status status, int work_progress);
  virtual void          on_task_end(task_status status, int work_total);
  virtual bool          is_task_cancelled() const;
  
protected:
  virtual void          run_task() = 0;
  virtual QString       get_progress_label() const;
  virtual void          set_progress_label(QString label);
  cartridge*            m_cartridge;
  
private:
  std::mutex*           m_mutex;
  QProgressDialog*      m_progress;
  QString               m_progress_label;
  
  usb::usb_device*      m_usb;
  linkmasta_device*     m_linkmasta;
  
  libusb_context*       m_libusb;
  libusb_device*        m_device;
  libusb_device_handle* m_handle;
};

#endif // CARTRIDGETASK_H