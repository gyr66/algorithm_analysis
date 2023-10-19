require 'benchmark'

def generate_data(file_path, data_size)
  File.open(file_path, 'w') do |file|
    file.puts data_size
    data = Array.new(data_size) { rand(-2**31..2**31-1) }.join(' ')
    file.puts data
  end
end

def run_executable(executable_name, input_file_path, output_file_path)
  time = Benchmark.measure do
    system("#{executable_name} < #{input_file_path} > #{output_file_path}")
  end
  return (time.real * 1000).round(2)
end

def average_run(executable_name, data_size, input_file_path, output_file_path, times)
  total_time = 0.0
  times.times do
    generate_data(input_file_path, data_size)
    total_time += run_executable(executable_name, input_file_path, output_file_path)
  end
  avg_time = total_time / times
  return avg_time.round(2)
end


data_sizes = [10_000, 30_000, 50_000, 80_000, 100_000, 200_000, 2000_000]

data_sizes.each do |data_size|
  avg_quick_sort_time = average_run('quick_sort.exe', data_size, 'input.txt', 'output.txt', 3)
  avg_merge_sort_time = average_run('merge_sort_l.exe', data_size, 'input.txt', 'output.txt', 3)

  puts "Data Size: #{data_size}"
  puts format("Average merge_sort_l.exe Run Time: %.2f ms", avg_merge_sort_time)
  puts format("Average quick_sort.exe Run Time: %.2f ms", avg_quick_sort_time)
  puts "\n"
end
