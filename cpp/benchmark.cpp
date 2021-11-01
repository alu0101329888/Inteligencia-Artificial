#include "../hpp/mapa.hpp"
#include "../hpp/mundo.hpp"
#include "../hpp/taxi.hpp"
#include "../hpp/nodo.hpp"
#include <chrono>

void Benchmark() {
  Mundo benchmark;
  benchmark.Resize(300, 300);
  benchmark.RandomBenchmark(22500, 0, 0, 299, 299);
  Taxi benchmarkTaxi(benchmark, 0, 0, 299, 299);

  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                         --- Benchmark ---\n\n  Matriz 300x300 - 25% de obstáculos - 4 direcciones - Manhattan:       ";
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(0, 1);
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 300x300 - 25% de obstáculos - 4 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n";

  std::cout << "  Matriz 300x300 - 25% de obstáculos - 8 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 300x300 - 25% de obstáculos - 8 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n\n";

  benchmark.Empty();
  benchmark.Resize(300, 300);
  benchmark.RandomBenchmark(45000, 0, 0, 299, 299);
  benchmarkTaxi.BenchmarkSet(benchmark, 0, 0, 299, 299);

  std::cout << "  Matriz 300x300 - 50% de obstáculos - 4 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 300x300 - 50% de obstáculos - 4 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n";

  std::cout << "  Matriz 300x300 - 50% de obstáculos - 8 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 300x300 - 50% de obstáculos - 8 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n\n";

  benchmark.Empty();
  benchmark.Resize(300, 300);
  benchmark.RandomBenchmark(72000, 0, 0, 299, 299);
  benchmarkTaxi.BenchmarkSet(benchmark, 0, 0, 299, 299);

  std::cout << "  Matriz 300x300 - 80% de obstáculos - 4 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 300x300 - 80% de obstáculos - 4 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n";

  std::cout << "  Matriz 300x300 - 80% de obstáculos - 8 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 300x300 - 80% de obstáculos - 8 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n\n\n\n\n";

  benchmark.Empty();
  benchmark.Resize(150, 150);
  benchmark.RandomBenchmark(5625, 0, 0, 149, 149);
  benchmarkTaxi.BenchmarkSet(benchmark, 0, 0, 149, 149);

  std::cout << "  Matriz 150x150 - 25% de obstáculos - 4 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 150x150 - 25% de obstáculos - 4 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n";

  std::cout << "  Matriz 150x150 - 25% de obstáculos - 8 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 150x150 - 25% de obstáculos - 8 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n\n";

  benchmark.Empty();
  benchmark.Resize(150, 150);
  benchmark.RandomBenchmark(11250, 0, 0, 149, 149);
  benchmarkTaxi.BenchmarkSet(benchmark, 0, 0, 149, 149);

  std::cout << "  Matriz 150x150 - 50% de obstáculos - 4 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 150x150 - 50% de obstáculos - 4 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n";

  std::cout << "  Matriz 150x150 - 50% de obstáculos - 8 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 150x150 - 50% de obstáculos - 8 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n\n";

  benchmark.Empty();
  benchmark.Resize(150, 150);
  benchmark.RandomBenchmark(18000, 0, 0, 149, 149);
  benchmarkTaxi.BenchmarkSet(benchmark, 0, 0, 149, 149);

  std::cout << "  Matriz 150x150 - 80% de obstáculos - 4 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 150x150 - 80% de obstáculos - 4 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo4(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n";

  std::cout << "  Matriz 150x150 - 80% de obstáculos - 8 direcciones - Manhattan:       ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(0, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n";

  std::cout << "  Matriz 150x150 - 80% de obstáculos - 8 direcciones - Euclidea:        ";
  begin = std::chrono::steady_clock::now();
  benchmarkTaxi.CaminoMinimo8(1, 1);
  end = std::chrono::steady_clock::now();
  std::cout << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000 << " milisegundos\n\n\n";
}