#ifndef _RISCV_GDBSERVER_H
#define _RISCV_GDBSERVER_H

#include <stdint.h>

class sim_t;

template <typename T>
class circular_buffer_t
{
public:
  // The buffer can store capacity-1 data elements.
  circular_buffer_t(unsigned int capacity) : data(new T[capacity]),
      start(0), end(0), capacity(capacity) {}
  circular_buffer_t() : start(0), end(0), capacity(0) {}
  ~circular_buffer_t() { delete[] data; }

  T *data;
  unsigned int start;   // Data start, inclusive.
  unsigned int end;     // Data end, exclusive.
  unsigned int capacity;    // Size of the buffer.
  unsigned int size() const;
  bool empty() const { return start == end; }
  bool full() const { return ((end+1) % capacity) == start; }

  // Return size and address of the block of RAM where more data can be copied
  // to be added to the buffer.
  unsigned int contiguous_empty_size() const;
  T *contiguous_empty() { return data + end; }
  void data_added(unsigned int bytes);

  unsigned int contiguous_data_size() const;
  T *contiguous_data() { return data + start; }
  // Tell the buffer that some bytes were consumed from the start of the
  // buffer.
  void consume(unsigned int bytes);

  void reset();

  T operator[](unsigned int i) const { return data[(start + i) % capacity]; }

  void append(const T *src, unsigned int count);
};

// Class to track software breakpoints that we set.
class software_breakpoint_t
{
public:
  reg_t address;
  unsigned int size;
  uint32_t instruction;

  void insert(mmu_t* mmu);
  void remove(mmu_t* mmu);
};

class gdbserver_t
{
public:
  // Create a new server, listening for connections from localhost on the given
  // port.
  gdbserver_t(uint16_t port, sim_t *sim);

  // Process all pending messages from a client.
  void handle();

  void handle_packet(const std::vector<uint8_t> &packet);
  void handle_interrupt();

  void handle_breakpoint(const std::vector<uint8_t> &packet);
  void handle_continue(const std::vector<uint8_t> &packet);
  void handle_extended(const std::vector<uint8_t> &packet);
  void handle_general_registers_read(const std::vector<uint8_t> &packet);
  void handle_halt_reason(const std::vector<uint8_t> &packet);
  void handle_kill(const std::vector<uint8_t> &packet);
  void handle_memory_binary_write(const std::vector<uint8_t> &packet);
  void handle_memory_read(const std::vector<uint8_t> &packet);
  void handle_query(const std::vector<uint8_t> &packet);
  void handle_register_read(const std::vector<uint8_t> &packet);
  void handle_register_write(const std::vector<uint8_t> &packet);
  void handle_step(const std::vector<uint8_t> &packet);

  bool connected() const { return client_fd > 0; }

private:
  sim_t *sim;
  int socket_fd;
  int client_fd;
  circular_buffer_t<uint8_t> recv_buf;
  circular_buffer_t<uint8_t> send_buf;

  bool expect_ack;
  bool extended_mode;
  // Used to track whether we think the target is running. If we think it is
  // but it isn't, we need to tell gdb about it.
  bool running;

  std::map <reg_t, software_breakpoint_t> breakpoints;

  // Read pending data from the client.
  void read();
  void write();
  // Accept a new client if there isn't one already connected.
  void accept();
  // Process all complete requests in recv_buf.
  void process_requests();
  // Add the given message to send_buf.
  void send(const char* msg);
  // Hex-encode a 64-bit value, and send it to gcc in target byte order (little
  // endian).
  void send(uint64_t value);
  // Hex-encode a 32-bit value, and send it to gcc in target byte order (little
  // endian).
  void send(uint32_t value);
  void send_packet(const char* data);
  uint8_t running_checksum;
  void send_running_checksum();

  // Write value to the index'th word in Debug RAM.
  void write_debug_ram(unsigned int index, uint32_t value);
};

#endif
