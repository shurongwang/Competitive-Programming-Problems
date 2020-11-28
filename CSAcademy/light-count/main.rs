const BB: u8 = 6;
const B: u8 = 1 << BB;
const FULL: u8 = B - 1;
const N: usize = 50000000;
const C: usize = (N >> BB) + 1;

static mut bits: [u64; C] = [0; C];

struct Generator {
	a: i32, b: i32, c: i32
}

impl Generator {
	#[inline(always)]
	fn get(&mut self) -> usize {
		let t: i32 = self.a ^ (self.a << 11);
		self.a = self.b;
		self.b = self.c;
		self.c ^= (self.c >> 19) ^ t ^ (t >> 8);
		self.c as usize
	}

	#[inline(always)]
	fn rand(&mut self, size: usize) -> usize { self.get() % size }
}

struct FenwickTree {
	tr: [i32; C]
}
static mut tr: FenwickTree = FenwickTree { tr: [0; C] };

impl FenwickTree {
	#[inline(always)]

	#[inline(always)]
	fn upd(&mut self, mut u: usize, w: i32) {
		u += 1;
		while u <= C {
			unsafe { *self.tr.get_unchecked_mut(u) += w; }
			u += u & (!u + 1);
		}
	}

	#[inline(always)]
	fn qry(&mut self, mut u: usize) -> i32 {
		let mut r: i32 = 0;
		u += 1;
		while u > 0 {
			unsafe { r += *self.tr.get_unchecked_mut(u); }
			u -= u & (!u + 1);
		}
		return r;
	}
}

#[inline(always)]
fn count(a: u64, l: u8) -> i32 { (a << l).count_ones() as i32 }

#[inline(always)]
fn flip(id: usize) {
	let i: usize = id >> BB;
	let j: u8 = (id as u8) & FULL;
	unsafe {
		*bits.get_unchecked_mut(i) ^= 1 << j;
		tr.upd(i, if (*bits.get_unchecked(i) >> j & 1) == 1 { 1 } else { -1 });
	}
}

#[inline(always)]
fn qry(to: usize) -> i32 {
	let i: usize = to >> BB;
	let j: u8 = to as u8 & FULL;
	unsafe { tr.qry(i - 1) + count(*bits.get_unchecked(i), FULL - j) }
}

#[inline(always)]
fn query(l: usize, r: usize) -> i32 { qry(r) - if l == 0 { 0 } else { qry(l - 1) } }

fn main() {
	let mut ans: i64 = 0;
	let mut gen: Generator = Generator { a: 0, b: 0, c: 0 };
	
	let mut buffer = String::new();
	::std::io::stdin().read_line(&mut buffer).expect("Unable to read line");
	let mut iter = buffer.trim().split(' ');
	let n = iter.next().unwrap().parse::<usize>().unwrap();
	let m = iter.next().unwrap().parse::<usize>().unwrap();
	gen.a = iter.next().unwrap().parse::<i32>().unwrap();
	gen.b = iter.next().unwrap().parse::<i32>().unwrap();
	gen.c = iter.next().unwrap().parse::<i32>().unwrap();
	
	for i in 0 .. m {
		let tp = gen.rand(2);
		if tp == 0 {
			let id = gen.rand(n);
			flip(id);
		} else {
			let mut l = gen.rand(n);
			let mut r = gen.rand(n);
			if l > r { std::mem::swap(&mut l, &mut r); }
			ans ^= i as i64 * query(l, r) as i64;
		}
	}
	println!("{}", ans);
}