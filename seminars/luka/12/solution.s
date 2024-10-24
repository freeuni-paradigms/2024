# we recommend writing basic offsets here
# variables, struct members, struct sizes



struct cpu {
  int id;			#0 offset
  short cores[2];	#4 offset
};

struct serverRoom {
  char *model; 		#0 offset
  struct cpu node;	#4 offset
  struct cpu *next;	#12 offset
};

typedef char* (*bootstrapScript)(struct cpu*);

bootstrapScript GetSetupScript(char* model);
struct cpu **SetupServers(struct cpu *server, bootstrapScript script);

struct cpu **CreateComputerLab(short *roomNumber, struct serverRoom *servers)
{
  roomNumber[*roomNumber] = 0;
  if (servers[2].node.id > 3)
    servers += ((struct cpu *) (servers->next[0].cores))->id;
  bootstrapScript localScript = GetSetupScript(servers[0].model);
  return SetupServers((struct cpu *)&servers, localScript);
}

# roomNumber[*roomNumber] === *(roomNumber + *roomNumber)


# line 1
# roomNumber[*roomNumber] = 0;

addi x10, sp, 4  # x10 = &roomNumber (short**)
lw x10, 0(x10)	 # x10 = roomNumber  (short*)
lh x11, 0(x10)   # x11 = *roomNumber (short)
li x12, 2
mul x11, x11, x12
add x12, x10, x11
sh x0, 0(x12)


# line 2
# if (servers[2].node.id > 3)

addi x10, sp, 8 	# &servers
lw x10, 0(x10)		# servers
addi x11, x0, 16
addi x12, x0, 2
mul x13, x12, x11	# 16 * 2
add x14, x10, x13	# x14 = servers + 2
addi x15, x14, 4	# x15 = &servers[2].node = &servers[2].node.id
lw x16, 0(x15)		# x16 = servers[2].node.id
addi x17, x0, 3
BLE x16, x17, CONTINUE


# line 3
# servers += ((struct cpu *) (servers->next[0].cores))->id;

# int arr[4];
# &arr = arr = &arr[0]
#
addi x10, sp, 8 	# &servers
lw x10, 0(x10)		# servers
addi x11, x10, 12 	# &servers[0].next
lw x12, 0(x11)      # servers[0].next
addi x13, x12, 4    # servers[0].next[0].cores
lw x14, 0(x13)      # ((struct cpu *) (servers->next[0].cores))->id;
muli x15, x14, 16   # zemota * serveris_zoma
add x16, x15, x10   # servers + zemota * serveris_zoma
sw x16, 8(sp)

# line 4
# bootstrapScript localScript = GetSetupScript(servers[0].model);

CONTINUE:




# line 5
# return SetupServers((struct cpu *)&servers, localScript);




typedef struct {
	int arr[32];
	// raghacebi
} vector;


// void *base (4 bytes)
// arr[0]
//
//
//
//
//
//